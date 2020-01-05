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

using namespace std;

/**
 * is_quoted return true if string is between quotes else false
 */
bool is_quoted(const string &str) // האם הוא בין מרכאות
{
    return str[0] == '"' && str[str.length() - 1] == '"';
}
/**
 * strip_quote return string that between quotes without quotes
 * @param str string with quotes
 * @return string without quotes
 */
string strip_quotes(const string &str) // מפשיט ממרכאות את ״בלה5״ להיות בלה5
{
    if (!is_quoted(str)) throw StrIsNotBetweenQuotes();

    return str.substr(1, str.length() - 2);
}
/**.
 * connectControlClient try connect to control client with port that in input
 * throw error if not seccsed connect to server or if not have appropriate argument
 * @param iter to place in vector for the port
 * @return iter to next command in vector
 */
vector<string>::iterator connectControlClientCommand::execute(vector<string>::iterator iter)
{
//    cout << "at connectControlClient. iter is at ";
//    cout << *iter << " $ " << *(iter + 1) << " $ " << *(iter + 2) << " $ " << *(iter + 3) << endl;

    try // try open the client
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
 * openServerCommand  try open to server with port that in input
 * throw error if not seccsed connect to client or if not have appropriate argument
 * @param iter to place in vector for the port
 * @return iter to next command in vector
 */
vector<string>::iterator openDataServerCommand::execute(vector<string>::iterator iter)
{
//    cout << "at openServerCommand. iter is at ";
//    cout << *iter << " $ " << *(iter + 1) << " $ " << *(iter + 2) << " $ " << *(iter + 3) << endl;

    try
    {
        int port = stoi(*iter);
        app::globals->server = new FromAeroplaneServer(port);
        app::globals->server->run();
    }
    catch (TelnetServer::ServerError_AcceptingClientFailed &err)
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
 * printCommand print to the console the string in vector
 * @param iter to place in vector for the string
 * @return iter to next command in vector
 */
vector<string>::iterator printCommand::execute(vector<string>::iterator iter)
{
//    cout << "at printCommand. iter is at ";
//    cout << *iter << " $ " << *(iter + 1) << " $ " << *(iter + 2) << " $ " << *(iter + 3) << endl;

    if (is_quoted(*iter)) // if have quoted in string, this is string, print him
    {
        cout << strip_quotes(*iter) << endl;
    }
    else // this is num or expression, evealuate him and print him
    {
        cout << evaluateExpressionStr(*iter) << endl;
    }

    return iter + 1;
}
/**
 * sleep the main thread acurdding the number in vector
 * if this is variable or expresion find him value and sleep for him
 * @param iter the place input in vector
 * @return iter to next command in vector
 */
vector<string>::iterator sleepCommand::execute(vector<string>::iterator iter)
{
//    cout << "at sleepCommand. iter is at ";
//    cout << *iter << " $ " << *(iter + 1) << " $ " << *(iter + 2) << " $ " << *(iter + 3) << endl;

    long millisToSleep = (long) evaluateExpressionStr(*iter);

    this_thread::sleep_for(chrono::milliseconds((millisToSleep)));

    return iter + 1;
}
/**
 * createVarCommand create new var according the input. two kind var:
 * var update according the var that simulator send to program <-
 * var that send to simulator and update him on value ->
 * local var. not to be sent, nor received. =
 * @param iter the place input in vector
 * @return iter to next command in vector
 */
vector<string>::iterator createVarCommand::execute(vector<string>::iterator iter)
{
//    cout << "at createVarCommand. iter is at ";
//    cout << *iter << " $ " << *(iter + 1) << " $ " << *(iter + 2) << " $ " << *(iter + 3) << endl;

    string name = *iter++;

    if (*iter == "->") // var that need send to simulator
    {
        if (*++iter != "sim") throw VarDeclarationNotLegal(); // if not have address var

        iter++;

        string address = strip_quotes(*iter++); // return string without quotes

        app::globals->do_with_vars_map([&]() //update var map
        {
            app::globals->varsMap->operator[](name) = new Var(address,Var::toBeSentToSimulator);
        });
    }
    else if (*iter == "<-") // var that need update from simulator
    {
        if (*++iter != "sim") throw VarDeclarationNotLegal();// if not have address var

        iter++;

        string address = strip_quotes(*iter++);// return string without quotes

        app::globals->do_with_vars_map([&]()//update var map
        {
            app::globals->varsMap->operator[](name) = new Var(address);
            app::globals->server->keepThisVarUpdated(app::globals->varsMap->at(name));
        });
    }
    else if (*iter == "=") // a local var. not to be sent, nor received.
    {
        app::globals->do_with_vars_map([&]() // update map
        {
            app::globals->varsMap->operator[](name) = new Var;
        });

        iter = updateVarCommand::execute(iter - 1);
    }
    else throw VarDeclarationNotLegal();

    return iter;
}
/**
 * updateVarCommand update var in map
 * @param iter the place input in vector
 * @return iter to next command in vector
 */
vector<string>::iterator updateVarCommand::execute(vector<string>::iterator iter)
{
    // "rudder", "=", "(h0 - heading)/80"

//    cout << "at updateVarCommand. iter is at ";
//    cout << *iter << " $ " << *(iter + 1) << " $ " << *(iter + 2) << " $ " << *(iter + 3) << endl;

    string name = *iter++;
    if (*iter++ != "=") throw VarAssigningNotLegal();
    string expression_str = *iter++;

    // evaluateExpression must be called when the mutex is unlocked
    double value = evaluateExpressionStr(expression_str); // may throw 'AssigningInvalidExpression'

    app::globals->do_with_vars_map([&]() //update map
    {
        Var* var = app::globals->varsMap->at(name);

        var->data = value;

        if (var->kind == Var::toBeSentToSimulator) //if need send to simulator, send him
        {
            app::globals->client->send_var_to_aeroplane(*var);
        }
    });

    return iter;
}
/**
 * ifCommand play the block command if the condition true.
 * if the condition true, send block to perser
 * @param iter the place input in vector
 * @return iter to next command in vector
 */
vector<string>::iterator ifCommand::execute(vector<string>::iterator iter)
{
//    cout << "at ifCommand. iter is at ";
//    cout << *iter << " $ " << *(iter + 1) << " $ " << *(iter + 2) << " $ " << *(iter + 3) << endl;

    //    iter
    //     |
    //     V
    // if, x + 7 * y, >=, y * 9 - 6, {, x, =, y + 4 - 2 * x, },

    condition cond    //information of condition
    {
            Interpreter::interpret(*iter++),
            *iter++,
            Interpreter::interpret(*iter++)
    };


    // עכשיו איטר בדיוק על הפותח המסולסל

    /* todo
    auto endLoop = app::globals->matching_curly_brackets->at(iter);
     אבל כיוון שהמילון הזה לא מעודכן בינתיים:
     */
//    auto endLoop = iter;
//    while (*++endLoop != "}");
    // עכשיו אנדלופ בדיוק על הסוגר המסולסk
    auto endLoop = app::globals->matching_curly_brackets->at(iter); // iter to end block
    if (cond.check())//if condition true, play parse with him block
    {
        parse(iter + 1, endLoop);
    }
    return endLoop + 1;
}

/**
 * check the condition accurding the opertor string
 * @return true or false if the condition right or not.
 */
bool condition::check()
{
    _left->update_values(); // update the condition expression according map
    _right->update_values();

    auto left = _left->expression->calculate(); // calculate condition expression
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
/**
 * while command remove the condition string to condition
 * and play all black while until the condition not true
 * @param iter the place input in vector
 * @return iter to next command in vector
 */
vector<string>::iterator whileCommand::execute(vector<string>::iterator iter)
{
//    cout << "at whileCommand. iter is at ";
//    cout << *iter << " $ " << *(iter + 1) << " $ " << *(iter + 2) << " $ " << *(iter + 3) << endl;

    condition cond //information of condition
    {
            Interpreter::interpret(*iter++),
            *iter++,
            Interpreter::interpret(*iter++)
    };

    auto endLoop = app::globals->matching_curly_brackets->at(iter);// iter to end block

    while (cond.check()) //while condition true, play parse with him block
    {
        parse(iter + 1, endLoop);
    }
    return endLoop + 1;
}