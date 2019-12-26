//
// Created by hodyah on 20/12/2019.
//

#ifndef FLIGHT_PROJECT_SIMPLECOMMANDFROMFILETOMAP_H
#define FLIGHT_PROJECT_SIMPLECOMMANDFROMFILETOMAP_H

#include <unordered_map>
#include "command.h"
#include "server.h"
#include "Expression.h"
#include "controlFly.h"
#include "thread"
#include "chrono"
/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 */
class connectControlClient: public command{
public:
//    connectControlClient(client clientPointer);
    void execute(vector<string>* inputVector, vector<string>::iterator* runOnVector);
};

/**
 * create server with the current input
 * and update thr queue
 */
class openServerCommand: public command{
    server *serverPointer;
public:
    openServerCommand(server *serverPointer);
    void execute(vector<string>* inputVector, vector<string>::iterator* runOnVector);
};
/**
 * printCommand print to the console the string
 * @param inputQueue the comman queue
 */
class printCommand: public command {
    //ToDo add map and check if print var from map
public:
    void execute(vector<string>* inputVector, vector<string>::iterator* runOnVector);
};
/**
 * sleep the main thread acurdding the number in queue
 * @param inputQueue the command queue
 */
class sleepCmmand: public command{
    //ToDo add map and check if print var from map
public:
    sleepCmmand();
    void execute(vector<string>* inputVector, vector<string>::iterator* runOnVector);
};
/**
 *
 */
class varCommand: public command{
    unordered_map<string, Expression> *varMapSendClient;
    unordered_map<string, Expression> *varMapUpdateServer;
public:
    varCommand(unordered_map<string, Expression> *mapClient, unordered_map<string, Expression> *mapServer);
    void execute(vector<string>* inputVector, vector<string>::iterator* runOnVector);
};

#endif //FLIGHT_PROJECT_SIMPLECOMMANDFROMFILETOMAP_H
