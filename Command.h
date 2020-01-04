//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_COMMAND_H
#define FLIGHT_PROJECT_COMMAND_H

#include <vector>
#include "ExpressionInterpreter.h"


struct Command {
    virtual std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) = 0;

    virtual ~Command() = default;
};

class VarDeclarationNotLegal : std::exception {};


/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 */
class connectControlClientCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};

/**
 * create server with the current input
 * and update thr queue
 */
class openDataServerCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};

/**
 * printCommand print to the console the string
 * @param inputQueue the comman queue
 */
class printCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};

/**
 * sleep the main thread acurdding the number in queue
 * @param inputQueue the command queue
 */
class sleepCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};


class updateVarCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};

class createVarCommand : public updateVarCommand {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};




/*********************************/
/** IF / WHILE CODE GOES HERE **/
/******************************/





/**
 * ifCommand play the block command if the condition true.
 * @param controlFly the control fly object
 */
class ifCommand : public Command { // todo ...להשתמש בירושה כלשהי כי הקוד של איף ושל ווייל די דומה
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};

/**
 * while command remove the condition string to condition
 * and play all black while until the condition not true
 * @param controlFly the control fly object
 */
class whileCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};

/**
 * struct to create condition information: exp, operator, exp
 */
struct condition {

    ExpressionWrapper *_left = nullptr;
    std::string _operator;
    ExpressionWrapper *_right = nullptr;

    bool check();

    ~condition()
    {
        delete _left;
        delete _right;
    }

    class InvalidConditionOperator : std::exception {};

    class ExpressionCouldNotBeCalculated : std::exception {};
};

#endif // FLIGHT_PROJECT_COMMAND_H
