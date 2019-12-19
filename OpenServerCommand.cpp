//
// Created by hodyah on 19/12/2019.
//
#include "OpenServerCommand.h"
#include "server.h"

/**
 * create server with the current input
 * and update thr queue
 */
OpenServerCommand:: OpenServerCommand(): command(){
};
void OpenServerCommand:: execut(queue<string>* inputQueue){
    try{
        server serverOpen(atof((inputQueue->front().c_str())));
        inputQueue->pop();
    } catch (...) {
        return;
    }
}

