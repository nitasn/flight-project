//
// Created by hodyah on 20/12/2019.
//
//#include "simpleCommandFromFileToMap.h"
//#include "TelnetClient.h"
//#include "TelnetServer.h"
//#include "Command.h"
//#include "ToAeroplaneClient.h"
//#include "FromAeroplaneServer.h"
//#include "environment.h"
//#include "ExpressionInterpreter.h"
//#include "parser.h"
//
//#include <cmath>
//
//
//bool is_quoted(const string& str) // האם הוא בין מרכאות
//{
//    return str[0] == '"' && str[str.length() - 1] == '"';
//}
//
//string strip_quotes(const string& str) // מפשיט ממרכאות את ״בלה5״ להיות בלה5
//{
//    if (!is_quoted(str)) throw "str is not between quotes";
//
//    return str.substr(1, str.length() - 2);
//}
//
///**.
// * connectControlClient connect to control client with the
// * current input and update thr queue
// * @param inputQueue the comman queue
// */
//vector<string>::iterator connectControlClient:: execute(vector<string>::iterator iter)
//{
//    try
//    {
//        string ip_address = strip_quotes(*iter++);
//        int port = stoi(*iter++);
//        environment->client = new ToAeroplaneClient(port);
//    }
//    catch (TelnetClient::CouldNotConnectToServer& err)
//    {
//        cerr << "open client command failed: network error" << endl;
//        throw err;
//    }
//    catch (invalid_argument& err)
//    {
//        cerr << "open client command failed: invalid port" << endl;
//        throw err;
//    }
//
//    return iter;
//}
///**
// * openServerCommand create server with the current input
// * and update thr queue
// * @param inputQueue the comman queue
// */
//vector<string>::iterator openServerCommand:: execute(vector<string>::iterator iter)
//{
//    try
//    {
//        int port = stoi(*iter);
//        environment->server = new FromAeroplaneServer(port);
//        environment->server->run();
//    }
//    catch (TelnetServer::serverNetworkError& err)
//    {
//        cerr << "open client command failed: network error" << endl;
//        throw err;
//    }
//    catch (invalid_argument& err)
//    {
//        cerr << "open client command failed: invalid port" << endl;
//        throw err;
//    }
//    return iter + 1;
//}
///**
// * printCommand print to the console the string
// * @param inputQueue the comman queue
// */
//vector<string>::iterator printCommand::execute(vector<string>::iterator iter)
//{
//    if (is_quoted(*iter))
//    {
//        cout << strip_quotes(*iter);
//    }
//    else
//    {
//        auto exp = Interpreter::interpret(*iter);
//        exp->update_values();
//        cout << exp->expression->calculate() << endl;
//        delete exp;
//    }
//
//    return iter + 1;
//}
//
///**
// *
// * @param mapClient
// * @param mapServer
// */
//
///**
// * sleep the main thread acurdding the number in queue
// * if this is variable or expresion find him value and sleep
// * for him
// * @param iter the itartor to vector
// */
//vector<string>::iterator sleepCommand::execute(vector<string>::iterator iter)
//{
//    auto exp = Interpreter::interpret(*iter);
//    exp->update_values();
//    long millisToSleep = (long)exp->expression->calculate();
//    delete exp;
//
//   this_thread::sleep_for(chrono::milliseconds((millisToSleep)));
//
//   return iter + 1;
//}
//
//vector<string>::iterator createVarCommand::execute(vector<string>::iterator iter)
//{
//    string name = *iter++;
//
//    if (*iter == "->")
//    {
//        if (*++iter != "sim") throw VarDeclarationNotLegal();
//
//        environment->synchronously_with_vars_map([&]()
//        {
//            environment->varsMap->operator[](name) =
//                    new Var(*++iter++, Var::toBeSentToSimulator);
//        });
//    }
//    else if (*iter == "<-")
//    {
//        if (*++iter != "sim") throw VarDeclarationNotLegal();
//
//        environment->synchronously_with_vars_map([&]()
//        {
//            environment->varsMap->operator[](name) = new Var(*++iter++);
//        });
//
//        environment->server->keepThisVarUpdated(name);
//    }
//    else if (*iter == "=")
//    {
//        environment->synchronously_with_vars_map([&]()
//        {
//            environment->varsMap->operator[](name) = new Var(*++iter);
//        });
//
//        iter = updateVarCommand::execute(iter - 1);
//    }
//    else throw VarDeclarationNotLegal();
//
//    return iter;
//}
//
//vector<string>::iterator updateVarCommand::execute(vector<string>::iterator iter)
//{
//    // "rudder", "=", "(h0 - heading)/80"
//
//    string name = *iter++;
//    if (*iter++ != "=") throw VarAssigningNotLegal();
//    string expression_str = *iter++;
//
//    // evaluateExpression must be called when the mutex is unlocked
//    double value = evaluateExpression(expression_str); // may throw 'AssigningInvalidExpression'
//
//    environment->synchronously_with_vars_map([&]()
//    {
//        environment->varsMap->operator[](name)->data = value;
//
//        if (environment->varsMap->at(name)->kind == Var::toBeSentToSimulator)
//        {
//            environment->client->send_var_to_aeroplane(name);
//        }
//    });
//
//    return iter;
//}
