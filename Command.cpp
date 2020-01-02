//
// Created by Nitsan BenHanoch on 02/01/2020.
//

#include "TelnetClient.h"
#include "TelnetServer.h"
#include "Command.h"
#include "ToAeroplaneClient.h"
#include "FromAeroplaneServer.h"
#include "globals_singleton.h"
#include "ExpressionInterpreter.h"
#include "parser.h"

#include <cmath>

class StrIsNotBetweenQuotes : exception
{
};

bool is_quoted(const string &str) // האם הוא בין מרכאות
{
    return str[0] == '"' && str[str.length() - 1] == '"';
}

string strip_quotes(const string &str) // מפשיט ממרכאות את ״בלה5״ להיות בלה5
{
    if (!is_quoted(str)) throw StrIsNotBetweenQuotes();

    return str.substr(1, str.length() - 2);
}

/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 * @param inputQueue the comman queue
 */
vector<string>::iterator connectControlClient::execute(vector<string>::iterator iter)
{
    try
    {
        string ip_address = strip_quotes(*iter++);
        int port = stoi(*iter++);
        app::globals->client = new ToAeroplaneClient(port);
    }
    catch (TelnetClient::CouldNotConnectToServer &err)
    {
        cerr << "open client command failed: network error" << endl;
        throw err;
    }
    catch (invalid_argument &err)
    {
        cerr << "open client command failed: invalid port" << endl;
        throw err;
    }

    return iter;
}

/**
 * openServerCommand create server with the current input
 * and update thr queue
 * @param inputQueue the comman queue
 */
vector<string>::iterator openServerCommand::execute(vector<string>::iterator iter)
{
    try
    {
        int port = stoi(*iter);
        app::globals->server = new FromAeroplaneServer(port);
        app::globals->server->run();
    }
    catch (TelnetServer::serverNetworkError &err)
    {
        cerr << "open client command failed: network error" << endl;
        throw err;
    }
    catch (invalid_argument &err)
    {
        cerr << "open client command failed: invalid port" << endl;
        throw err;
    }
    return iter + 1;
}

/**
 * printCommand print to the console the string
 * @param inputQueue the comman queue
 */
vector<string>::iterator printCommand::execute(vector<string>::iterator iter)
{
    if (is_quoted(*iter))
    {
        cout << strip_quotes(*iter) << endl;
    }
    else
    {
        cout << evaluateExpressionStr(*iter) << endl;
    }

    return iter + 1;
}

/**
 *
 * @param mapClient
 * @param mapServer
 */

/**
 * sleep the main thread acurdding the number in queue
 * if this is variable or expresion find him value and sleep
 * for him
 * @param iter the itartor to vector
 */
vector<string>::iterator sleepCommand::execute(vector<string>::iterator iter)
{
    long millisToSleep = (long) evaluateExpressionStr(*iter);

    this_thread::sleep_for(chrono::milliseconds((millisToSleep)));

    return iter + 1;
}

vector<string>::iterator createVarCommand::execute(vector<string>::iterator iter)
{
    string name = *iter++;

    if (*iter == "->")
    {
        if (*++iter != "sim") throw VarDeclarationNotLegal();

        string address = strip_quotes(*++iter++);

        app::globals->do_with_vars_map([&]()
        {
            app::globals->varsMap->operator[](name) = new Var(address,Var::toBeSentToSimulator);
        });
    }
    else if (*iter == "<-")
    {
        if (*++iter != "sim") throw VarDeclarationNotLegal();

        string address = strip_quotes(*++iter++);

        app::globals->do_with_vars_map([&]()
        {
            app::globals->varsMap->operator[](name) = new Var(address);
        });

        app::globals->server->keepThisVarUpdated(name);
    }
    else if (*iter == "=")
    {
        app::globals->do_with_vars_map([&]()
        {
            app::globals->varsMap->operator[](name) = new Var(*++iter);
        });

        iter = updateVarCommand::execute(iter - 1);
    }
    else throw VarDeclarationNotLegal();

    return iter;
}

vector<string>::iterator updateVarCommand::execute(vector<string>::iterator iter)
{
    // "rudder", "=", "(h0 - heading)/80"

    string name = *iter++;
    if (*iter++ != "=") throw VarAssigningNotLegal();
    string expression_str = *iter++;

    // evaluateExpression must be called when the mutex is unlocked
    double value = evaluateExpressionStr(expression_str); // may throw 'AssigningInvalidExpression'

    app::globals->do_with_vars_map([&]()
    {
        app::globals->varsMap->operator[](name)->data = value;
        if (app::globals->varsMap->at(name)->kind == Var::toBeSentToSimulator) {
            app::globals->client->send_var_to_aeroplane(name);
        }
    });

    return iter;
}





/*********************************/
/** IF / WHILE CODE GOES HERE **/
/******************************/







/**
 * ifCommand play the block command if the condition true.
 * @param controlFly the control fly object
 */
vector<string>::iterator ifCommand::execute(vector<string>::iterator iter)
{
    // if, x + 7, <=, y * 9 - 6, {, x, =, y + 4 - 2 * x, },
    auto *cond = new condition(iter);
    bool condition_holds = cond->check();
    delete cond;

    iter += 3; // now we are at the '{'

    // todo next line should always work. no try/catch needed. if missing paren then lexer would've thrown exception
    auto endLoop = app::globals->matching_curly_brackets->at(iter);

    if (condition_holds) {
        parse(iter + 1, endLoop);
    }
    return endLoop + 1;
}

/**
 * check the condition accurding the opertor string
 * @param ifCondition the condition information
 * @return true or false if the condition right or not.
 */
bool condition::check()
{
    _left->update_values(); // מציבים את
    _right->update_values(); // המשתנים שבביטויים

    auto left = _left->expression->calculate();
    auto right = _right->expression->calculate();

    if (isnan(left) || isnan(right)) throw ExpressionCouldNotBeCalculated();

    if (_operator == ">=") return left >= right;

    if (_operator == "<=") return left <= right;

    if (_operator == "==") return left == right;

    if (_operator == ">") return left > right;

    if (_operator == "<") return left < right;

    if (_operator == "!=") return left != right;

    throw InvalidConditionOperator();
}

condition::condition(vector<string>::iterator iter)
{
    // todo does sending an iter by value copy the entire vector? i hope not

    _left = Interpreter::interpret(*iter); // מחזיר גם ביטוי וגם את המשתנים שבו

    _operator = *(iter + 1);

    _right = Interpreter::interpret(*(iter + 2));
}

/**
 * while command remove the condition string to condition
 * and play all black while until the condition not true
 * @param controlFly the control fly object
 */
vector<string>::iterator whileCommand::execute(vector<string>::iterator iter)
{
    // while, x + 7, <=, y * 9 - 6, {, x, =, y + 4 - 2 * x, },
    auto *cond = new condition(iter);

    iter += 3; // now we are at the '{'

    auto endLoop = app::globals->matching_curly_brackets->at(iter++);

    while (cond->check()) {
        parse(iter, endLoop);
    }

    delete cond;
    return endLoop + 1;
}