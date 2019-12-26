//
// Created by hodyah on 25/12/2019.
//
#include "ifWhileCommandFromFileToMap.h"
/**
 * ifCommand play the block command if the condition true.
 * @param controlFly the control fly object
 */
ifCommand::ifCommand(parser *parserFile){
    this->parserFile = parserFile;
}
void ifCommand:: execute(vector<string>* inputVector, vector<string>::iterator* runOnVector){
    condition ifCondition = returnConditionFromString(inputVector, runOnVector);
    if(checkCondition(ifCondition)){
        while((**runOnVector) != "}"){
            this->parserFile->playParser(runOnVector);
        }
    }
    delete ifCondition.secondExpression, ifCondition.firstExpresion;
    delete(ifCondition.secondExpression, ifCondition.firstExpresion);
}
/**
 * function to create condition from three first in queue
 * @param inputQueue string queue with the condition
 * @return the condition strucr with two expression and string opertor
 */
condition returnConditionFromString(vector<string>* inputVector, vector<string>::iterator* runOnVector){
    condition currentCondition;
    Interpreter* firstInterpter = new Interpreter();
    currentCondition.firstExpresion = firstInterpter->interpret(**runOnVector);
    (*runOnVector)++;
    currentCondition.conditionOpertor = **runOnVector;
    (*runOnVector)++;
    Interpreter* secondInterpter = new Interpreter();
    currentCondition.secondExpression = secondInterpter->interpret(**runOnVector);
    (*runOnVector)++;
    delete firstInterpter, secondInterpter;
    delete (firstInterpter, secondInterpter);
    return currentCondition;
}
/**
 * check the condition accurding the opertor string
 * @param ifCondition the condition information
 * @return true or false if the condition right or not.
 */
bool checkCondition(condition ifCondition){
    if(ifCondition.conditionOpertor == ">="){
        if(ifCondition.firstExpresion->calculate() >= ifCondition.secondExpression->calculate()){
            return true;
        }
    } else if(ifCondition.conditionOpertor == "<="){
        if(ifCondition.firstExpresion->calculate() <= ifCondition.secondExpression->calculate()){
            return true;
        }
    } else if(ifCondition.conditionOpertor == "<"){
        if(ifCondition.firstExpresion->calculate() < ifCondition.secondExpression->calculate()){
            return true;
        }
    }else if(ifCondition.conditionOpertor == ">"){
        if(ifCondition.firstExpresion->calculate() > ifCondition.secondExpression->calculate()){
            return true;
        }
    }else if(ifCondition.conditionOpertor == "!="){
        if(ifCondition.firstExpresion->calculate() != ifCondition.secondExpression->calculate()){
            return true;
        }
    }else{
        if(ifCondition.firstExpresion->calculate() == ifCondition.secondExpression->calculate()){
            return true;
        }
    }
    return false;
}
/**
 * while command remove the condition string to condition
 * and play all black while until the condition not true
 * @param controlFly the control fly object
 */
whileCommand::whileCommand(parser *parserFile) {
    this->parserFile = parserFile;
}
void whileCommand::execute(vector<string> *inputVector, vector<string>::iterator* runOnVector) {
    //TODO run on loop save the command
    condition whileCondition = returnConditionFromString(inputVector, runOnVector);
    vector<string>::iterator beginTheLoop = *runOnVector;
    while(checkCondition(whileCondition)){
        runOnVector = &beginTheLoop;
        while(**runOnVector != "}"){
            this->parserFile->playParser(runOnVector);
        }
    }
    delete whileCondition.secondExpression, whileCondition.firstExpresion;
    delete(whileCondition.secondExpression, whileCondition.firstExpresion);
}