//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef TESTION_PARSER_H
#define TESTION_PARSER_H

#include <iostream>
#include <map>
#include "command.h"
#include "CommandFactory.h"

using namespace std;
class VarAssigningNotLegal : std::exception {};
void parse(vector<string>::iterator iter, vector<string>::iterator end);
double evaluateExpression(string& exp_str);
#endif //TESTION_PARSER_H
