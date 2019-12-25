#include "controlFly.h"
#include "lexer.h"
#include "simpleCommandFromFileToMap.h"
#include "ifWhileCommandFromFileToMap.h"

//
// Created by hodyah on 20/12/2019.
//
/**
 * controlFly class control all the act in the play.
 * play all the function, save all information and update
 * the method accurding what they need
 */
void controlFly::playControlFly(string fileCommandName) {
    try{
        lexer lexerFile(fileCommandName);
        this->commandQueue = lexerFile.splitFile();
    } catch (...){
        printf("problem with lexer. check your file");
        return;
    }
    this->serverObject = new server();
//    this->varMapSendClient = new unordered_map<string, Expression>();
//    this->varMapUpdateServer = new unordered_map<string, Expression>();
//    this->clientObject = new client();
    try{
        mapOfCommmand();
        while(!this->commandQueue->empty()) {
            parser();
        }
    }catch (...){
//        delete(*this->varMapUpdateServer, *this->varMapSendClient,
//                *this->commandQueue, this->serverObject);
    }
    //TODO close the client and server
//    delete(*this->varMapUpdateServer, *this->varMapSendClient,
//            *this->commandQueue, this->serverObject);
}
/**
 * parser pop the queue map and do play the command
 */
void controlFly::parser() {
    if (!this->commandMap.count(this->commandQueue->front()) == 0) {
        command currentCommand = this->commandMap[this->commandQueue->front()];
        this->commandQueue->pop();
        currentCommand.execut(this->commandQueue);
    } else {
//            if(!this->varMapUpdateServer.count(this->commandQueue->front()) == 0){
//
//            }
//            if (!this->varMapSendClient.count(this->commandQueue->front()) == 0){
//
//            }
    }
}
/**
 *mapOfCommand input the map all the command with the current variable.
 */
void controlFly::mapOfCommmand() {
        //TODO check if can be sim alone
        //TODO check = or -> alone
        //TODO check if sim can be alone
    this->commandMap.insert(make_pair("openDataServer", openServerCommand(this->serverObject)));
    this->commandMap.insert(make_pair("connectControlClient", connectControlClient()));
//    this->commandMap.insert(make_pair("sim",));
//    this->commandMap.insert(make_pair("var",));
    this->commandMap.insert(make_pair("Print", printCommand()));
    this->commandMap.insert(make_pair("Sleep",sleepCmmand()));
    this->commandMap.insert(make_pair("while",whileCommand(this)));
    this->commandMap.insert(make_pair("if",ifCommand(this)));
}