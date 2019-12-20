//
// Created by hodyah on 19/12/2019.
//
#include "openServerCommand.h"
#include "server.h"

/**
 * openServerCommand create server with the current input
 * and update thr queue
 */
openServerCommand:: openServerCommand(server *serverPointer): command(){
    this->serverPointer = serverPointer;
};
void openServerCommand:: execut(queue<string>* inputQueue){
    try{
        this->serverPointer->openTheServer(atof((inputQueue->front().c_str())));
        inputQueue->pop();
    } catch (...) {
        return;
    }
}

