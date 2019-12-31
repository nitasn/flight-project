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

class VarDeclarationNotLegal : exception {};


/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 */
class connectControlClient: public Command{
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector) override;
};

/**
 * create server with the current input
 * and update thr queue
 */
class openServerCommand: public Command{
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector) override;
};
/**
 * printCommand print to the console the string
 * @param inputQueue the comman queue
 */
class printCommand: public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector) override;
};
/**
 * sleep the main thread acurdding the number in queue
 * @param inputQueue the command queue
 */
class sleepCmmand: public Command{
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector) override;
};


class updateVarCommand: public Command {
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector) override;
};

class createVarCommand: public updateVarCommand{
public:
    vector<string>::iterator execute(vector<string>::iterator runOnVector) override;
};

struct Var {

    enum kind { toBeSentToSimulator, notToBeSent};

    double data{};
    string addressInSimulator;
    kind kind = notToBeSent;

    explicit Var(string addressInSimulator, enum kind kind = notToBeSent) :
            addressInSimulator(move(addressInSimulator)), kind(kind) {}

    Var() { addressInSimulator = nullptr; } // for local vars
};

#endif //FLIGHT_PROJECT_SIMPLECOMMANDFROMFILETOMAP_H