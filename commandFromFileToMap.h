////
//// Created by hodyah on 20/12/2019.
////
//
//#ifndef FLIGHT_PROJECT_COMMANDFROMFILETOMAP_H
//#define FLIGHT_PROJECT_COMMANDFROMFILETOMAP_H
//
//#include <unordered_map>
//#include "command.h"
//#include "server.h"
//#include "Expression.h"
//
///**.
// * connectControlClient connect to control client with the
// * current input and update thr queue
// */
//class connectControlClient: public command{
//public:
////    connectControlClient(client clientPointer);
//    void execut(queue<string>* inputQueue);
//};
//
///**
// * create server with the current input
// * and update thr queue
// */
//class openServerCommand: public command{
//    server *serverPointer;
//public:
//    openServerCommand(server *serverPointer);
//    void execut(queue<string>* inputQueue);
//};
///**
// * printCommand print to the console the string
// * @param inputQueue the comman queue
// */
//class printCommand: public command {
//public:
//    void execut(queue<string>* inputQueue);
//};
///**
// *
// */
//class varCommand: public command{
//    unordered_map<string, Expression> *varMapSendClient;
//    unordered_map<string, Expression> *varMapUpdateServer;
//public:
//    varCommand(unordered_map<string, Expression> *mapClient, unordered_map<string, Expression> *mapServer);
//    void execut(queue<string>* inputQueue);
//};
//
//
//#endif //FLIGHT_PROJECT_COMMANDFROMFILETOMAP_H
