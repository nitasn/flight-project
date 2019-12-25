//
// Created by hodyah on 20/12/2019.
//
using namespace std;
#include <string>
#include <queue>
#include <fstream>
#include "iostream"
#include <unordered_map>
#include "command.h"
#include "server.h"
#include "Expression.h"
//#include "client.h"
#ifndef FLIGHT_PROJECT_CONTROLFLY_H
#define FLIGHT_PROJECT_CONTROLFLY_H
/**
 * controlFly class control all the act in the play.
 * play all the function, save all information and update
 * the method accurding what they need
 */
class controlFly{
    queue<string>* commandQueue;
    unordered_map<string, class command> commandMap;
    unordered_map<string, class Expression> *varMapUpdateServer;
    unordered_map<string, class Expression> *varMapSendClient;
    server *serverObject;
//    client clientObject;
public:
//    controlFly();
    void playControlFly(string fileCommandName);
    void parser();
private:
    void mapOfCommmand();
};
#endif //FLIGHT_PROJECT_CONTROLFLY_H
//
// Created by hodyah on 20/12/2019.
//
using namespace std;
#include <string>
#include <queue>
#include <fstream>
#include "iostream"
#include <unordered_map>
#include "command.h"
#include "server.h"
#include "Expression.h"
//#include "client.h"
#ifndef FLIGHT_PROJECT_CONTROLFLY_H
#define FLIGHT_PROJECT_CONTROLFLY_H
/**
 * controlFly class control all the act in the play.
 * play all the function, save all information and update
 * the method accurding what they need
 */
class controlFly{
    queue<string>* commandQueue;
    unordered_map<string, command> commandMap;
    unordered_map<string, Expression> *varMapUpdateServer;
    unordered_map<string, Expression> *varMapSendClient;
    server *serverObject;
//    client clientObject;
public:
//    controlFly();
    void playControlFly(string fileCommandName);
    void parser‬‬();
private:
    void mapOfCommmand();
};
#endif //FLIGHT_PROJECT_CONTROLFLY_H
