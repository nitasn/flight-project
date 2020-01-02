//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_COMMAND_H
#define FLIGHT_PROJECT_COMMAND_H

#include <vector>
#include "ExpressionInterpreter.h"

using namespace std;

struct Command {
    virtual vector<string>::iterator execute(vector<string>::iterator iter) = 0;

    virtual ~Command() = default;
};

class VarDeclarationNotLegal : exception {};


/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 */
class connectControlClient : public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator iter) override;
};

/**
 * create server with the current input
 * and update thr queue
 */
class openServerCommand : public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator iter) override;
};

/**
 * printCommand print to the console the string
 * @param inputQueue the comman queue
 */
class printCommand : public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator iter) override;
};

/**
 * sleep the main thread acurdding the number in queue
 * @param inputQueue the command queue
 */
class sleepCommand : public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator iter) override;
};


class updateVarCommand : public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector) override;
};

class createVarCommand : public updateVarCommand {
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector) override;
};




/*********************************/
/** IF / WHILE CODE GOES HERE **/
/******************************/




/**
 * ifCommand play the block command if the condition true.
 * @param controlFly the control fly object
 */
class ifCommand : public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator iter) override;
};

/**
 * while command remove the condition string to condition
 * and play all black while until the condition not true
 * @param controlFly the control fly object
 */
class whileCommand : public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator iter) override;
};

/**
 * struct to create condition information: exp, operator, exp
 */
struct condition {
    ExpressionWrapper *_left;
    string _operator;
    ExpressionWrapper *_right;

    bool check();

    class InvalidConditionOperator : exception {};

    class ExpressionCouldNotBeCalculated : exception {};

    /**
     * constructor receives vector<str>::iter, and takes the top three tokens to be
     * the left exp, the operator, and the right exp.
     */
    explicit condition(vector<string>::iterator iter);

    ~condition()
    {
        delete _left;
        delete _right;
    }
};

#endif // FLIGHT_PROJECT_COMMAND_H
