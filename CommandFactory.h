//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_COMMANDFACTORY_H
#define FLIGHT_PROJECT_COMMANDFACTORY_H

#include "Command.h"
#include <string>
#include <functional>
#include <map>


class CommandNotFound : std::exception {};

class CommandFactory
{
    static std::map<std::string, std::function<Command *()>> dict; // cmd_name -> lambda, that returns a cmd object

public:
    static Command *GetCmdObject(std::string &str);

    static bool IsCommand(std::string &str);
};
/**
 * to_lower change all word to lettle sign
 * @param str string accurding input
 * @return string of lettle sign
 */
std::string to_lower(std::string& str);


#endif // FLIGHT_PROJECT_COMMANDFACTORY_H
