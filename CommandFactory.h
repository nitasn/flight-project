//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_COMMANDFACTORY_H
#define FLIGHT_PROJECT_COMMANDFACTORY_H

#include "Command.h"
#include <string>
#include <functional>
#include <map>
#include "ifWhileCommandFromFileToMap.h"
#include "simpleCommandFromFileToMap.h"

using namespace std;

class CommandNotFound : exception {};

class CommandFactory
{
    static map<string, function<Command *()>> dict; // cmd_name -> lambda that returns a cmd object

public:
    static Command *GetCmdObject(string &str);

    static bool IsCommand(string &str);
};


#endif FLIGHT_PROJECT_COMMANDFACTORY_H
