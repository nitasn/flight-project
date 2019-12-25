//
// Created by hodyah on 25/12/2019.
//

#include "ifWhileCommandFromFileToMap.h"
/**
 * ifCommand play the block command if the condition true.
 * @param controlFly the control fly object
 */
ifCommand::ifCommand(class controlFly* controlFly){
    this->controlFlyObject = controlFly;
}
void ifCommand:: execut(queue<string>* inputQueue){
    condition ifCondition = returnConditionFromString(inputQueue);
    if(checkCondition(ifCondition)){
        while(inputQueue->front() != "}"){
            this->controlFlyObject->parser();
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
condition returnConditionFromString(queue<string>* inputQueue){
    condition currentCondition;
    Interpreter* firstInterpter = new Interpreter();
    currentCondition.firstExpresion = firstInterpter->interpret(inputQueue->front());
    inputQueue->pop();
    currentCondition.conditionOpertor = inputQueue->front();
    inputQueue->pop();
    Interpreter* secondInterpter = new Interpreter();
    currentCondition.secondExpression = secondInterpter->interpret(inputQueue->front());
    inputQueue->pop();
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
whileCommand::whileCommand(class controlFly *controlFly) {
    this->controlFlyObject = controlFly;
}
void whileCommand::execut(queue<string> *inputQueue) {
    condition whileCondition = returnConditionFromString(inputQueue);
    while(checkCondition(whileCondition)){
        while(inputQueue->front() != "}"){
            this->controlFlyObject->parser();
        }
    }
    delete whileCondition.secondExpression, whileCondition.firstExpresion;
    delete(whileCondition.secondExpression, whileCondition.firstExpresion);
}