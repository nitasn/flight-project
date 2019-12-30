//
// Created by hodyah on 20/12/2019.
//

#ifndef FLIGHT_PROJECT_SIMPLECOMMANDFROMFILETOMAP_H
#define FLIGHT_PROJECT_SIMPLECOMMANDFROMFILETOMAP_H

#include <unordered_map>
#include "command.h"
#include "Expression.h"
#include "controlFly.h"
#include "thread"
#include "chrono"
/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 */
class connectControlClient: public Command{
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector);
};

/**
 * create server with the current input
 * and update thr queue
 */
class openServerCommand: public Command{
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector);
};
/**
 * printCommand print to the console the string
 * @param inputQueue the comman queue
 */
class printCommand: public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector);
};
/**
 * sleep the main thread acurdding the number in queue
 * @param inputQueue the command queue
 */
class sleepCmmand: public Command{
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector);
};
/**
 *
 */
class varCommand: public Command{
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector);
};

struct Var {
    double data{};
    string addressInSimulator;
    bool toBeSentToSimulator = false;
    explicit Var(string addressInSimulator, bool toBeSent = false) : addressInSimulator(move(addressInSimulator)),
                                                                        toBeSentToSimulator(toBeSent) {}
    Var() { addressInSimulator = nullptr; } // for local vars
};

#endif //FLIGHT_PROJECT_SIMPLECOMMANDFROMFILETOMAP_H