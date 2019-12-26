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
        this->commandVector = lexerFile.splitFile();
    } catch (...){
        printf("problem with lexer. check your file\n");
        return;
    }
    this->serverObject = new server();
//    this->varMapSendClient = new unordered_map<string, Expression>();
//    this->varMapUpdateServer = new unordered_map<string, Expression>();
//    this->clientObject = new client();
    try{
        mapOfCommand();
        this->parserFile = new parser(this->commandMap);
        vector<string>::iterator runOnVactor =  this->commandVector->begin();
        while(runOnVactor!= this->commandVector->end()) {
            this->parserFile->playParser(&runOnVactor);
        }
    }catch (...){
//        delete(*this->varMapUpdateServer, *this->varMapSendClient,
//                *this->commandQueue, this->serverObject);
    }
    //TODO close the client and server deldte the command in map
//    delete(*this->varMapUpdateServer, *this->varMapSendClient,
//            *this->commandQueue, this->serverObject);
}
/**
 *mapOfCommand input the map all the command with the current variable.
 */
void controlFly::mapOfCommand() {
    //TODO check if can be sim alone
    //TODO check = or -> alone
    //TODO check if sim can be alone
    this->commandMap["openDataServer"] = new openServerCommand(this->serverObject);
    this->commandMap["connectControlClient"] = new connectControlClient();
//    this->commandMap.insert(make_pair("sim",));
//    this->commandMap.insert(make_pair("var",));
    this->commandMap["Print"] = new printCommand();
    this->commandMap["Sleep"] = new sleepCmmand();
    this->commandMap["while"] = new whileCommand(this->parserFile);
    this->commandMap["if"] = new ifCommand(this->parserFile);
}
