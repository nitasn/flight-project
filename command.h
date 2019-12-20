//
// Created by hodyah on 19/12/2019.
//

#ifndef FLIGHT_PROJECT_COMMAND_H
#define FLIGHT_PROJECT_COMMAND_H
using namespace std;
#include <string>
#include "queue"
/**.
 * Command Pattern to pholemorfizm to use all command like one
 */
class command{
public:
    virtual void execut();
};
#endif //FLIGHT_PROJECT_COMMAND_H

