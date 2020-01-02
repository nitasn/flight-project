//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#include "CommandFactory.h"

bool CommandFactory::IsCommand(string &str)
{
    return dict.find(str) != dict.end();
}

Command *CommandFactory::GetCmdObject(string &str)
{
    if (!IsCommand(str)) throw CommandNotFound();

    return dict[str]();
}

map<string, function<Command *()>> CommandFactory::dict =
{
    {"if", []() { return new ifCommand(); }},
    {"print", []() { return new printCommand(); }},
    {"while", [](){ return new whileCommand(); }},
    {"sleep", [](){ return new sleepCommand(); }},
    {"openDataServer", [](){ return new openServerCommand(); }},
    {"connectControlClient", [](){ return new connectControlClient(); }},
    {"var", [](){ return new createVarCommand(); }}
};
