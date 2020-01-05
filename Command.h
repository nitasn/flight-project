//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_COMMAND_H
#define FLIGHT_PROJECT_COMMAND_H

#include <vector>
#include "ExpressionInterpreter.h"

/**
 * exception trhow if String Is Not Between Quotes
 */
class StrIsNotBetweenQuotes : std::exception{};
/**
 * abstarct command to play all kind command
 * have execute method and desconstructor
 */
struct Command {
    virtual std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) = 0;

    virtual ~Command() = default;
};

class VarDeclarationNotLegal : std::exception {};

/**.
 * connectControlClient try connect to control client with port that in input
 * throw error if not seccsed connect to server or if not have appropriate argument
 * @param iter to place in vector for the port
 * @return iter to next command in vector
 */
class connectControlClientCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};
/**
 * openServerCommand  try open to server with port that in input
 * throw error if not seccsed connect to client or if not have appropriate argument
 * @param iter to place in vector for the port
 * @return iter to next command in vector
 */
class openDataServerCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};
/**
 * printCommand print to the console the string in vector
 * @param iter to place in vector for the string
 * @return iter to next command in vector
 */
class printCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};
/**
 * sleep the main thread acurdding the number in vector
 * if this is variable or expresion find him value and sleep for him
 * @param iter the place input in vector
 * @return iter to next command in vector
 */
class sleepCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator iter) override;
};
/**
 * updateVarCommand update var in map
 * @param iter the place input in vector
 * @return iter to next command in vector
 */
class updateVarCommand : public Command {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};
/**
 * createVarCommand create new var according the input. two kind var:
 * var update according the var that simulator send to program <-
 * var that send to simulator and update him on value ->
 * local var. not to be sent, nor received. =
 * @param iter the place input in vector
 * @return iter to next command in vector
 */
class createVarCommand : public updateVarCommand {
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};
/**
 * ifCommand play the block command if the condition true.
 * if the condition true, send block to perser
 * @param iter the place input in vector
 * @return iter to next command in vector
 */
class ifCommand : public Command { // todo ...להשתמש בירושה כלשהי כי הקוד של איף ושל ווייל די דומה
public:
    std::vector<std::string>::iterator execute(std::vector<std::string>::iterator runOnVector) override;
};

/**
 * while command remove the condition string to condition
 * and play all black while until the condition not true
 * @param iter the place input in vector
 * @return iter to next command in vector
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
    /**
    * check the condition accurding the opertor string
    * @return true or false if the condition right or not.
     */
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
