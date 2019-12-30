#include "controlFly.h"
#include "lexer.h"
#include "simpleCommandFromFileToMap.h"
#include "ifWhileCommandFromFileToMap.h"
#include "singltonGlobals.h"
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
        this->lexerFile = (fileCommandName);
        this->commandVector = lexerFile.splitFile();
    } catch (...){
        printf("problem with lexer. check your file\n");
        return;
    }
    try{
        VarsMap::mutexSingleton.it = new mutex;
        VarsMap::mapSingleton.it = new map<string, Var*>;

        vector<string>::iterator runOnVactor =  this->commandVector->begin();
        parse(runOnVactor, this->commandVector->end());

        VarsMap::mutexSingleton.destruct();
        VarsMap::mapSingleton.destruct();

    }catch (...){
//        delete(*this->varMapUpdateServer, *this->varMapSendClient,
//                *this->commandQueue, this->serverObject);
    }
    //TODO close the client and server deldte the command in map
//    delete(*this->varMapUpdateServer, *this->varMapSendClient,
//            *this->commandQueue, this->serverObject);
}

///**
// *mapOfCommand input the map all the command with the current variable.
// */
//void controlFly::mapOfCommand() {
//    //TODO check if can be sim alone
//    //TODO check = or -> alone
//    //TODO check if sim can be alone
//    this->commandMap["openDataServer"] = new openServerCommand(this->serverObject);
//    this->commandMap["connectControlClient"] = new connectControlClient();
////    this->commandMap.insert(make_pair("var",));
//    this->commandMap["Print"] = new printCommand();
//    this->commandMap["Sleep"] = new sleepCmmand();
//    this->commandMap["while"] = new whileCommand(this->parserFile);
//    this->commandMap["if"] = new ifCommand(this->parserFile);
//}
