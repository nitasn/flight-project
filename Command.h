//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_COMMAND_H
#define FLIGHT_PROJECT_COMMAND_H
#include <vector>
#include <string>
using namespace std;
struct Command
{
    virtual vector<string>::iterator execute(vector<string>::iterator iter) = 0;
    virtual ~Command() = default;
};
#endif FLIGHT_PROJECT_COMMAND_H
