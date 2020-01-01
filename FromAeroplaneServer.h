//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_FROMAEROPLANESERVER_H
#define FLIGHT_PROJECT_FROMAEROPLANESERVER_H

#include <mutex>
#include "iostream"
#include "TelnetServer.h"
#include "var.h"

using namespace std;

class FromAeroplaneServer : public TelnetServer
{
    static const map<const string, int> measurements_indices;
    static const int num_measurements; // the size of 'measurements_indices'
    void process_data(const char *buffer, int buffer_size) override;
    set<string> toKeepUpdated;
    mutex mutex_dealing_with_the_set; // so we do not add items to the set while iterating over it

public:
    explicit FromAeroplaneServer(int portNum) : TelnetServer(portNum) {}
    void keepThisVarUpdated(string varName);
};

#endif FLIGHT_PROJECT_FROMAEROPLANESERVER_H
