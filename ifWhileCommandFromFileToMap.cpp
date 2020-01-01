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
        try{
            auto endLoop = MapItToBeginBracketSingleton::getMatchingParen(runOnVector);
            parse(runOnVector, endLoop);
        }
        catch(exception exp){throw exp;}
//        vector<string>::iterator& endOfIf = runOnVector;
//        parse(++runOnVector);
    } else{
//        while(*runOnVector != "}"){runOnVector++;}
        try{runOnVector = MapItToBeginBracketSingleton::getMatchingParen(runOnVector);}
        catch(exception exp){throw exp;}
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
    condition* res_cond = new condition; // result condition
    Interpreter leftExpInter;
    res_cond->leftExp = leftExpInter.interpret(*runOnVector++);
    res_cond->opCondition= *runOnVector++;
    Interpreter rightExpInter;
    res_cond->rightExp = rightExpInter.interpret(*runOnVector++);
    return res_cond;
}

/**
 * check the condition accurding the opertor string
 * @param ifCondition the condition information
 * @return true or false if the condition right or not.
 */
bool condition::check(){
    if(opCondition == ">=")
    {
        return leftExp->calculate() >= rightExp->calculate();
    }
    if(opCondition == "<=")
    {
        return leftExp->calculate() <= rightExp->calculate();
    }
    if(opCondition == "==")
    {
        return leftExp->calculate() == rightExp->calculate();
    }
    if(opCondition == ">")
    {
        return leftExp->calculate() > rightExp->calculate();
    }
    if(opCondition == "<")
    {
        return leftExp->calculate() < rightExp->calculate();
    }
    if(opCondition == "!=")
    {
        return leftExp->calculate() != rightExp->calculate();
    }
    throw InvalidConditionOperator();
}
/**
 * while command remove the condition string to condition
 * and play all black while until the condition not true
 * @param controlFly the control fly object
 */
vector<string>::iterator whileCommand:: execute(vector<string>::iterator runOnVector){
    condition whileCondition = *returnConditionFromString(runOnVector);
//    vector<string>::iterator beginTheLoop = runOnVector;
    runOnVector += 3;
    //todo why we need flag?
    bool flagIWaseCheck = false;
    while(checkCondition(whileCondition)){
        flagIWaseCheck = true;
//        runOnVector = beginTheLoop;
        try{
            auto endLoop = MapItToBeginBracketSingleton::getMatchingParen(runOnVector);
            parse(runOnVector, endLoop);
        }
        catch(exception exp){throw exp;}
    }
    if(!flagIWaseCheck){
        //todo we have this in the map, we dont need run again
//        while(*runOnVector != "}"){runOnVector++;}
        try{runOnVector = MapItToBeginBracketSingleton::getMatchingParen(runOnVector);}
        catch(exception exp){throw exp;}
    }
    delete whileCondition.rightExp, whileCondition.leftExp;
    delete(whileCondition.rightExp, whileCondition.leftExp);
    return runOnVector; // todo ++?
}