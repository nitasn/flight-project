//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#include "CommandFactory.h"
#include <sstream>

using namespace std;

/**
 * to_lower change all word to lettle sign
 * @param str string accurding input
 * @return string of lettle sign
 */
string to_lower(string& str) // לאותיות קטנות
{
    stringstream ss;

    for(auto c : str)
    {
        ss << (char) std::tolower(c);
    }

    return ss.str();
}
/**
 * return if this string is command
 * @param str string to check
 * @return true if this command, else false
 */
bool CommandFactory::IsCommand(string &str)
{
    return dict.find(to_lower(str)) != dict.end();
}
/**
 * GetCmdObject return new command accurding the string
 * @param str string with command name
 * @return new command object
 */
Command *CommandFactory::GetCmdObject(string &str)
{
    if (!IsCommand(str)) throw CommandNotFound();

    return dict[to_lower(str)]();
}
/**
 * dict with command object
 */
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
