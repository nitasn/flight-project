//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#include "CommandFactory.h"
#include <sstream>

using namespace std;


string to_lower(string& str) // לאותיות קטנות
{
    stringstream ss;

    for(auto c : str)
    {
        ss << (char) std::tolower(c);
    }

    return ss.str();
}

bool CommandFactory::IsCommand(string &str)
{
    return dict.find(to_lower(str)) != dict.end();
}

Command *CommandFactory::GetCmdObject(string &str)
{
    if (!IsCommand(str)) throw CommandNotFound();

    return dict[to_lower(str)]();
}

map<string, function<Command *()>> CommandFactory::dict =
{
    {"if", []() { return new ifCommand(); }},
    {"print", []() { return new printCommand(); }},
    {"while", [](){ return new whileCommand(); }},
    {"sleep", [](){ return new sleepCommand(); }},
    {"opendataserver", [](){ return new openDataServerCommand(); }},
    {"connectcontrolclient", [](){ return new connectControlClientCommand(); }},
    {"var", [](){ return new createVarCommand(); }}
};
