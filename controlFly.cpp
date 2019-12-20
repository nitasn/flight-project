#include "controlFly.h"
#include "lexer.h"

//
// Created by hodyah on 20/12/2019.
//
/**
 * controlFly class control all the act in the play.
 * play all the function, save all information and update
 * the method accurding what they need
 */
void controlFly::playControlFly(string fileCommandName) {
//    unordered_map<> varMapUp
//    unordered_map<> varMapSe
//    server serverObject;
//    client clientObject;
    try{
        lexer lexerFile(fileCommandName);
        this->commandQueue = lexerFile.splitFile();
    } catch (...){
        printf("problem with lexer. check your file");
        return;
    }



}

void controlFly::parser‬‬() {
    while(!this->commandQueue->empty()){
        command currentCommand = this->commandMap[this->commandQueue->front()];
        currentCommand.execut();
    }
    delete(this->commandQueue);
}
