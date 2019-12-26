//
// Created by hodyah on 25/12/2019.
//
#ifndef FLIGHT_PROJECT_IFWHILECOMMANDFROMFILETOMAP_H
#define FLIGHT_PROJECT_IFWHILECOMMANDFROMFILETOMAP_H
#include "controlFly.h"
/**
 * ifCommand play the block command if the condition true.
 * @param controlFly the control fly object
 */
class ifCommand: public command{
    parser *parserFile;
public:
    ifCommand(parser *parserFile);
    void execute(vector<string>* inputVector, vector<string>::iterator* runOnVector);
};
/**
 * struct to create condition information
 */
struct {
    Expression* firstExpresion;
    string conditionOpertor;
    Expression* secondExpression;
} typedef condition;
/**
 * function to create condition from three first in queue
 * @param inputQueue string queue with the condition
 * @return the condition strucr with two expression and string opertor
 */
condition returnConditionFromString(vector<string>* inputVector, vector<string>::iterator* runOnVector);
/**
 * check the condition accurding the opertor string
 * @param ifCondition the condition information
 * @return true or false if the condition right or not.
 */
bool checkCondition(condition ifCondition);
/**
 * while command remove the condition string to condition
 * and play all black while until the condition not true
 * @param controlFly the control fly object
 */
class whileCommand: public command{
    parser *parserFile
public:
    whileCommand(parser *parserFile);
    void execute(vector<string>* inputVector, vector<string>::iterator* runOnVector);
};
//TODO run on while
#endif //FLIGHT_PROJECT_IFWHILECOMMANDFROMFILETOMAP_H
