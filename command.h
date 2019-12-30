//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef TESTION_COMMAND_H
#define TESTION_COMMAND_H
#include <vector>
#include <string>
using namespace std;
struct Command
{
    virtual vector<string>::iterator execute(vector<string>::iterator iter) = 0;
    virtual ~Command() = default;
};
#endif //TESTION_COMMAND_H
