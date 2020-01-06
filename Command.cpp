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
 * strip_quote return the string between the quotes
 */
string strip_quotes(const string &str) // מפשיט ממרכאות את ״בלה5״ להיות בלה5
{
    if (!is_quoted(str)) throw StrIsNotBetweenQuotes();

    return str.substr(1, str.length() - 2);
}
/**.
 * connectControlClient connect to simulator with our client.
 * throws if fails
 * @param iter is expected to be at our args
 * @return iter exactly after our args
 */
vector<string>::iterator connectControlClientCommand::execute(vector<string>::iterator iter)
{
    try // open the client
    {
        string ip_address = strip_quotes(*iter++);

        string expression_str = *iter++;
        // evaluateExpression must be called when the mutex is unlocked
        int port = (int)evaluateExpressionStr(expression_str);

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
 * openServerCommand open server (in thread) to update vars from simulator
 * throws if fails
 * @param iter is expected to be at our args
 * @return iter exactly after our args
 */
vector<string>::iterator openDataServerCommand::execute(vector<string>::iterator iter)
{
    try
    {
        string expression_str = *iter++;

        // evaluateExpression must be called when the mutex is unlocked
        int port = (int)evaluateExpressionStr(expression_str);

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
    return iter;
}

/**
 * printCommand prints to standard stream one argument
 * @param iter is expected to be at our args
 * @return iter exactly after our args
 */
vector<string>::iterator printCommand::execute(vector<string>::iterator iter)
{
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
 * force main thread to sleep # milliseconds
 * @param iter is expected to be at our args
 * @return iter exactly after our args
 */
vector<string>::iterator sleepCommand::execute(vector<string>::iterator iter)
{
    long millisToSleep = (long) evaluateExpressionStr(*iter);

    this_thread::sleep_for(chrono::milliseconds((millisToSleep)));

    return iter + 1;
}
/**
 * createVarCommand declare a variable. may be of one of three kinds, distinguished by the operator:
 * "="  a local regular var
 * "->" has to be sent to simulator via our client every time value changes
 * "<-" updated constantly by a dedicated thread (our server) with values sent from simulator
 * @param iter is expected to be at our args
 * @return iter exactly after our args
 */
vector<string>::iterator createVarCommand::execute(vector<string>::iterator iter)
{
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
 * updateVarCommand update var in map (also send to simulator if bounded "->")
 * @param iter is expected to be at our args
 * @return iter exactly after our args
 */
vector<string>::iterator updateVarCommand::execute(vector<string>::iterator iter)
{
    // iter: |
    //       V
    //       rudder  =  (h0 - heading)/80

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
 * ifCommand evaluates condition and, if true, parses (a process that also runs) inner block
 * @param iter is expected to be at our args
 * @return iter exactly after our args
 */
vector<string>::iterator ifCommand::execute(vector<string>::iterator iter)
{
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

    auto endLoop = app::globals->matching_curly_brackets->at(iter); // location of closing "}"

    if (cond.check())//if condition true, play parse with him block
    {
        parse(iter + 1, endLoop);
    }
    return endLoop + 1;
}

/**
 * plugs current vars' values into expressions, evaluates them, and return whether condition holds now or not
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
 * while condition (from iter) evaluates to true, parse (a process that also runs: ) inner block
 * @param iter is expected to be at our args
 * @return iter exactly after our args
 */
vector<string>::iterator whileCommand::execute(vector<string>::iterator iter)
{
    //       iter
    //        |
    //        V
    // while, x + 7 * y, >=, y * 9 - 6, {, x, =, y + 4 - 2 * x, },
    condition cond //information of condition
    {
            Interpreter::interpret(*iter++),
            *iter++,
            Interpreter::interpret(*iter++)
    };

    auto endLoop = app::globals->matching_curly_brackets->at(iter); // location of closing "}"

    while (cond.check()) //while condition true, play parse with him block
    {
        parse(iter + 1, endLoop);
    }
    return endLoop + 1;
}