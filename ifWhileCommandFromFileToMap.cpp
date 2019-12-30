//
// Created by hodyah on 25/12/2019.
//
#include "ifWhileCommandFromFileToMap.h"
/**
 * ifCommand play the block command if the condition true.
 * @param controlFly the control fly object
 */
vector<string>::iterator ifCommand::execute(vector<string>::iterator runOnVector){
    condition ifCondition = returnConditionFromString(runOnVector);
    if(checkCondition(ifCondition)){
        vector<string>::iterator& endOfIf = runOnVector;
        parse(++runOnVector);
    } else{
        while(*runOnVector != "}"){runOnVector++;}
    }
    delete ifCondition.secondExpression, ifCondition.firstExpresion;
    delete(ifCondition.secondExpression, ifCondition.firstExpresion);
    return runOnVector; //todo ++?
}
/**
 * function to create condition from three first in queue
 * @param inputQueue string queue with the condition
 * @return the condition strucr with two expression and string opertor
 */
condition returnConditionFromString(vector<string>::iterator* runOnVector){
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
vector<string>::iterator whileCommand:: execute(vector<string>::iterator runOnVector){
    condition whileCondition = returnConditionFromString(runOnVector);
    vector<string>::iterator beginTheLoop = runOnVector;
    bool flagIWaseCheck = false;
    while(checkCondition(whileCondition)){
        flagIWaseCheck = true;
        runOnVector = beginTheLoop;
        parse(runOnVector);
    }
    if(!flagIWaseCheck){
        while(*runOnVector != "}"){runOnVector++;}
    }
    delete whileCondition.secondExpression, whileCondition.firstExpresion;
    delete(whileCondition.secondExpression, whileCondition.firstExpresion);
    return runOnVector; // todo ++?
}