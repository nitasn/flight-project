//
// Created by hodyah on 25/12/2019.
//
#include "ifWhileCommandFromFileToMap.h"
/**
 * ifCommand play the block command if the condition true.
 * @param controlFly the control fly object
 */
vector<string>::iterator ifCommand::execute(vector<string>::iterator runOnVector)
{
    // if, x + 7, <=, y * 9 - 6, {, x, =, y + 4 - 2 * x, },

    condition* ifCondition = returnConditionFromString(runOnVector);

    // עשיתי פה בלאגן
    // יש סוגריים מסולסלים בפלט של הלקסר? נראה לי שיעזור לנו אם יהיו לפחות לצורך דיבוג

    runOnVector += 3;

    if(ifCondition->check())
    {
        vector<string>::iterator& endOfIf = runOnVector;
        parse(++runOnVector);
    } else{
        while(*runOnVector != "}"){runOnVector++;}
    }
    delete ifCondition;

    return runOnVector; //todo ++?
}

/**
 * function to create condition from three first in queue
 * @param inputQueue string queue with the condition
 * @return the condition strucr with two expression and string opertor
 */
condition* returnConditionFromString(vector<string>::iterator runOnVector)
{
    auto* res_cond = new condition; // result condition

    res_cond->left_exp = interpreter.interpret(*runOnVector++);

    res_cond->_operator = *runOnVector++;

    res_cond->right_exp = interpreter.interpret(*runOnVector++);

    return res_cond;
}

/**
 * check the condition accurding the opertor string
 * @param ifCondition the condition information
 * @return true or false if the condition right or not.
 */
bool condition::check()
{
    if(_operator == ">=")
    {
        return left_exp->calculate() >= right_exp->calculate();
    }
    if(_operator == "<=")
    {
        return left_exp->calculate() <= right_exp->calculate();
    }
    if(_operator == "==")
    {
        return left_exp->calculate() == right_exp->calculate();
    }
    if(_operator == ">")
    {
        return left_exp->calculate() > right_exp->calculate();
    }
    if(_operator == "<")
    {
        return left_exp->calculate() < right_exp->calculate();
    }
    if(_operator == "!=")
    {
        return left_exp->calculate() != right_exp->calculate();
    }
    throw InvalidConditionOperator();
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
    delete whileCondition.right_exp, whileCondition.left_exp;
    delete(whileCondition.right_exp, whileCondition.left_exp);
    return runOnVector; // todo ++?
}