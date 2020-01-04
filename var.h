#ifndef FLIGHT_PROJECT_VAR_H
#define FLIGHT_PROJECT_VAR_H

struct Var
{
    enum kind { toBeSentToSimulator, notToBeSent};

    double data = 0;
    kind kind = notToBeSent;
    std::string addressInSimulator;

    explicit Var(std::string& addressInSimulator, enum kind kind = notToBeSent) // for in/out vars
    {
        this->addressInSimulator = addressInSimulator;
        this->kind = kind;
    }

    Var() = default; // for local vars
};

#endif