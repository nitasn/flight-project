//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_COMMAND_H
#define FLIGHT_PROJECT_COMMAND_H

#include <vector>
#include "ExpressionInterpreter.h"

class StrIsNotBetweenQuotes : std::exception{};

/**
 * handle args from iter, and do specific job with them
 */
struct Command {

    /**
     * @param iter is expected to be at our args
     * @return iter exactly after our args
     */
    virtual std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) = 0;

    virtual ~Command() = default;
};

class VarDeclarationNotLegal : std::exception {};

/**.
 * open client, connect to simulator, get ready to send data
 */
class connectControlClientCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};
/**
 * open server, wait on main thread for simulator to respond, then continue running in a different thread
 */
class openDataServerCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};
/**
 * sends whatever is on iter to std::cout. if it's an expression, evaluates it first
 */
class printCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};
/**
 * sleep # milliseconds on main thread. if arg is an expression, evaluate it first
 */
class sleepCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};
/**
 * update varsMap, and if var's kind is "->", tell client to send new value to simulator
 */
class updateVarCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};
/**
 * create a new var in varsMap, bound to "->", "<-", or "=" if local
 */
class createVarCommand : public updateVarCommand {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};
/**
 * evaluates condition, and if true, runs inner block from iter
 */
class ifCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};

/**
 * while evaluates to true, runs inner block from iter
 */
class whileCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};

/**
 * holds condition information: exp, operator, exp
 */
struct condition {

    ExpressionWrapper *_left = nullptr;
    std::string _operator;
    ExpressionWrapper *_right = nullptr;

    /** plugs current vars' values into expressions, evaluates them, and return whether condition holds now or not */
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
