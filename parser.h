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

void parse(std::vector<std::string>::iterator iter, std::vector<std::string>::iterator end);

double evaluateExpressionStr(std::string &exp_str);

#endif // FLIGHT_PROJECT_PARSER_H
