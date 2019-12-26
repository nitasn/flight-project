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
void connectControlClient:: execute(vector<string>* inputVector, vector<string>::iterator* runOnVector){
    try{
//        server serverOpen(atof((inputQueue->front().c_str())));
        (*runOnVector)++;
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
void openServerCommand:: execute(vector<string>* inputVector, vector<string>::iterator* runOnVector){
    try{
        this->serverPointer->openTheServer(atof(((*runOnVector)->c_str())));
        (*runOnVector)++;
    } catch (...) {
        return;
    }
}
/**
 * printCommand print to the console the string
 * @param inputQueue the comman queue
 */
void printCommand::execute(vector<string>* inputVector, vector<string>::iterator* runOnVector) {
    cout << **runOnVector << endl;
    (*runOnVector)++;
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
void varCommand::execute(vector<string>* inputVector, vector<string>::iterator* runOnVector)  {
    //TODO
    string varName = **runOnVector;
    (*runOnVector)++;
    if(**runOnVector == "->"){

    } else if(**runOnVector == "<-"){

    } else if(**runOnVector == "="){

    }
}
/**
 * sleep the main thread acurdding the number in queue
 * @param inputQueue the command queue
 */
void sleepCmmand::execute(vector<string>* inputVector, vector<string>::iterator* runOnVector)  {
    this_thread::sleep_for(chrono::seconds(atoi(((*runOnVector)->c_str()))));
    (*runOnVector)++;
}