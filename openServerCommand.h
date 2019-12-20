//
// Created by hodyah on 19/12/2019.
//

#ifndef FLIGHT_PROJECT_OPENSERVERCOMMAND_H
#define FLIGHT_PROJECT_OPENSERVERCOMMAND_H
#include "command.h"
#include "server.h"

/**
 * create server with the current input
 * and update thr queue
 */
class openServerCommand: public command{
    server *serverPointer;
public:
    openServerCommand(server *serverPointer);
    void execut(queue<string>* inputQueue);
};
#endif //FLIGHT_PROJECT_OPENSERVERCOMMAND_H
