//
// Created by hodyah on 26/12/2019.
//
using namespace std;
#include "string"
#include "iostream"
#include "command.h"
#include "Expression.h"
#include <fstream>
#include <unordered_map>
#include "lexer.h"
#include "parser.h"

#ifndef FLIGHT_PROJECT_CONTROLFLY_H
#define FLIGHT_PROJECT_CONTROLFLY_H
class controlFly{
    lexer lexerFile;
    vector<string>* commandVector;
    unordered_map<string, Command*> commandMap;
    unordered_map<string, Expression*>* varMap = new unordered_map<string, Expression*>();
public:
    void playControlFly(string fileCommandName);
    void mapOfCommand();
};
#endif //FLIGHT_PROJECT_CONTROLFLY_H
