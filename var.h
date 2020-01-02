#ifndef FLIGHT_PROJECT_VAR_H
#define FLIGHT_PROJECT_VAR_H

struct Var
{
    enum kind { toBeSentToSimulator, notToBeSent};

    double data{};
    std::string addressInSimulator;
    kind kind = notToBeSent;

    explicit Var(std::string addressInSimulator, enum kind kind = notToBeSent) :
            addressInSimulator(move(addressInSimulator)), kind(kind) {}

    Var() { addressInSimulator = nullptr; } // for local vars
};

#endif