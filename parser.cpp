//
// Created by hodyah on 26/12/2019.
//

#include "parser.h"
parser::parser(unordered_map<string, command*> commandMap) {
    this->commandMap = commandMap;
}
/**
 * parser pop the vector map and do play the command
 */
void parser::playParser(vector<string>::iterator* runOnVector) {
    if (this->commandMap.count(**runOnVector) != 0) {
        command* currentCommand = this->commandMap[**runOnVector];
        runOnVector++;
        currentCommand->execute(this->commandVector, runOnVector);
    } else {
//            if(!this->varMapUpdateServer.count(this->commandQueue->front()) == 0){
//
//            }
//            if (!this->varMapSendClient.count(this->commandQueue->front()) == 0){
//
//            }
    }
}
