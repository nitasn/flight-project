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

/*
    VarsMap::mutexSingleton.it->lock();
    map<string, Var *> * vars = VarsMap::mapSingleton.it;
    double x = vars["name"]->data;
    VarsMap::mutexSingleton.it->unlock();

 */

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
   int numToSleep = evaluateExpression(*runOnVector);
   runOnVector++;
   this_thread::sleep_for(chrono::seconds((numToSleep)));
    return ++runOnVector;
}