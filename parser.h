//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_PARSER_H
#define FLIGHT_PROJECT_PARSER_H

#include <iostream>
#include <map>
#include "Command.h"
#include "CommandFactory.h"

class VarAssigningNotLegal : std::exception{};

class UnknownCommand : std::exception{};
/**
 * parse while the vector command not ending, execute the commands.
 * create command with argument, or update var
 * @param iter to begin block in vector
 * @param end iter to end block
 */
void parse(std::vector<std::string>::iterator iter, std::vector<std::string>::iterator end);
/**
 * evaluateExpressionStr calculate expression that in string to num
 * @param exp_str string expression
 * @return value expression
 */
double evaluateExpressionStr(std::string &exp_str);

#endif // FLIGHT_PROJECT_PARSER_H
