//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef TESTION_COMMANDFACTORY_H
#define TESTION_COMMANDFACTORY_H

#include "command.h"
#include <string>
#include <functional>
#include <map>

using namespace std;

class CommandNotFound : exception {};

class CommandFactory
{
    static map<string, function<Command *()>> dict; // cmd_name -> lambda that returns a cmd object

public:
    static Command *GetCmdObject(string &str);

    static bool IsCommand(string &str);
};


#endif //TESTION_COMMANDFACTORY_H
