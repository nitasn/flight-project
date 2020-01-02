//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_PARSER_H
#define FLIGHT_PROJECT_PARSER_H

#include <iostream>
#include <map>
#include "Command.h"
#include "CommandFactory.h"

using namespace std;
class VarAssigningNotLegal : std::exception {};
class AssigningInvalidExpression : std::exception {};
void parse(vector<string>::iterator iter, vector<string>::iterator end);
double evaluateExpressionStr(string& exp_str);

#endif // FLIGHT_PROJECT_PARSER_H
