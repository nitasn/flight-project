//
// Created by hodyah on 26/12/2019.
//
#ifndef FLIGHT_PROJECT_CONTROLFLY_H
#define FLIGHT_PROJECT_CONTROLFLY_H
using namespace std;
#include "string"
#include "iostream"
#include "Command.h"
#include "Expression.h"
#include <fstream>
#include <unordered_map>
#include "parser.h"
#include "lexerFile.h"

class controlFly{
    lexerFile lexerFile;
    vector<string>* commandVector;
    unordered_map<string, Command*> commandMap;
    unordered_map<string, Expression*>* varMap = new unordered_map<string, Expression*>();
public:
    void playControlFly(string fileCommandName);
    void mapOfCommand();
};
#endif //FLIGHT_PROJECT_CONTROLFLY_H
