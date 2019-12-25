//
// Created by hodyah on 20/12/2019.
//
#include "simpleCommandFromFileToMap.h"
#include "server.h"
/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 * @param inputQueue the comman queue
 */
//connectControlClient:: connectControlClient(client *clientPointer): command(){
//    this->clienPointer = clientPointer;
//};
void connectControlClient:: execut(queue<string>* inputQueue){
    try{
//        server serverOpen(atof((inputQueue->front().c_str())));
        inputQueue->pop();
    } catch (...) {
        return;
    }
}
/**
 * openServerCommand create server with the current input
 * and update thr queue
 * @param inputQueue the comman queue
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
/**
 * printCommand print to the console the string
 * @param inputQueue the comman queue
 */
void printCommand::execut(queue<string> *inputQueue) {
    cout << inputQueue->front() << endl;
    inputQueue->pop();
}
/**
 *
 * @param mapClient
 * @param mapServer
 */
varCommand:: varCommand(unordered_map<string, Expression> *mapClient, unordered_map<string, Expression> *mapServer){
    this->varMapSendClient = mapClient;
    this->varMapUpdateServer = mapServer;
}
void varCommand::execut(queue<string> *inputQueue) {
    //TODO
    string varName = inputQueue->front();
    inputQueue->pop();
    if(inputQueue->front() == "->"){

    } else if(inputQueue->front() == "<-"){

    } else if(inputQueue->front() == "="){

    }
}
/**
 * sleep the main thread acurdding the number in queue
 * @param inputQueue the command queue
 */
void sleepCmmand::execut(queue<string> *inputQueue) {
    this_thread::sleep_for(chrono::seconds(atoi(inputQueue->front().c_str())));
    inputQueue->pop();
}