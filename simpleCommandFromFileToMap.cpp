//
// Created by hodyah on 20/12/2019.
//
#include "simpleCommandFromFileToMap.h"
#include "TelnetClient.h"
#include "TelnetServer.h"
#include "command.h"
#include "ToAeroplaneClient.h"
#include "FromAeroplaneServer.h"
#include "singltonGlobals.h"

#include <cmath>

/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 * @param inputQueue the comman queue
 */
vector<string>::iterator connectControlClient:: execute(vector<string>::iterator runOnVector){
    try {
        int port = stoi(*runOnVector);
        ToAeroplaneClientSingleton::it = new ToAeroplaneClient(port);
    }
    catch (TelnetClient::CouldNotConnectToServer& err)
    {
        cerr << "open client command failed: network error" << endl;
        throw err;
    }
    catch (invalid_argument& err)
    {
        cerr << "open client command failed: invalid port" << endl;
        throw err;
    }

    return runOnVector + 1;
}
/**
 * openServerCommand create server with the current input
 * and update thr queue
 * @param inputQueue the comman queue
 */
vector<string>::iterator openServerCommand:: execute(vector<string>::iterator runOnVector){
    try {
        int port = stoi(*runOnVector);
        FromAeroplaneServerSingleton::it = new FromAeroplaneServer(port);
        FromAeroplaneServerSingleton::it->run();
    }
    catch (TelnetServer::serverNetworkError& err)
    {
        cerr << "open client command failed: network error" << endl;
        throw err;
    }
    catch (invalid_argument& err)
    {
        cerr << "open client command failed: invalid port" << endl;
        throw err;
    }
    return ++runOnVector;
}
/**
 * printCommand print to the console the string
 * @param inputQueue the comman queue
 */
vector<string>::iterator printCommand::execute(vector<string>::iterator runOnVector) {
    double numToPrint = evaluateExpression(*runOnVector);
    cout << numToPrint << endl;
    return runOnVector + 1;
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
 * @param runOnVector the itartor to vector
 */
vector<string>::iterator sleepCmmand::execute(vector<string>::iterator runOnVector)  {

   long millisToSleep = lround(evaluateExpression(*runOnVector)); // תעגל לשלם הקרוב

   this_thread::sleep_for(chrono::milliseconds((millisToSleep)));

   return runOnVector + 1;
}

vector<string>::iterator createVarCommand::execute(vector<string>::iterator iter)
{
    string name = *iter++;

    VarsMap::mutexSingleton.it->lock();

    map<string, Var *> * vars = VarsMap::mapSingleton.it;

    vars->at(name) = new Var;

    if (*iter == "->")
    {
        if (*++iter != "sim") throw VarDeclarationNotLegal();

        vars->at(name)->addressInSimulator = *++iter++;

        VarsMap::mutexSingleton.it->unlock();
    }
    else if (*iter == "<-")
    {
        FromAeroplaneServerSingleton::it->keepThisVarUpdated(name); // מוסיף לקבוצת הדברים שצריכים להתעדכן ברקע כל הזמן

        if (*++iter != "sim") throw VarDeclarationNotLegal();

        vars->at(name)->addressInSimulator = *++iter++;

        VarsMap::mutexSingleton.it->unlock();
    }
    else if (*iter == "=")
    {
        VarsMap::mutexSingleton.it->unlock(); // unlocking it first because updateVarCommand will want to lock

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
    double value = evaluateExpression(expression_str); // may throw 'AssigningInvalidExpression'

    VarsMap::do_synchronously([&]() // מפעיל את הלוק של המפה, מריץ את הבלוק, ועושה אנלוק למפה
    {
        map<string, Var *> * vars = VarsMap::mapSingleton.it;
        vars->at(name)->data = value;

        if (vars->at(name)->kind == Var::toBeSentToSimulator)
        {
            ToAeroplaneClientSingleton::it->send_var_to_aeroplane(name);
        }
    });

    return iter;
}
