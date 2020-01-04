//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#include "FromAeroplaneServer.h"
#include "globals_singleton.h"

using namespace std;


void FromAeroplaneServer::process_data(const char *buffer, int buffer_size)
{
    double numbers_received[num_measurements];

    try {
        const string csv(buffer, buffer_size);

        const char comma = ',';
        int next_comma, prev_comma = 0, i = 0; // i == index of the double we are parsing now
        while ((next_comma = csv.find(comma, prev_comma)) != std::string::npos) // while next comma exists
        {
            numbers_received[i++] = stod(csv.substr(prev_comma, next_comma - prev_comma));
            prev_comma = next_comma + 1; // do not include this comma in the next substr
        }
        numbers_received[i] = stod(csv.substr(prev_comma)); // the value that's after the last comma
    }
    catch (...)
    {
        cerr << "server: error parsing data from aeroplane. data:" << endl
             << string(buffer, buffer_size) << endl
             << "was invalid and hence ignored." << endl;

        return;
    }

    mutex_dealing_with_the_set.lock();

    // no need to wrap with app::globals->do_with_vars_map([&]() { ... });
    // since we bypass varsMap and access our vars directly

    for (Var *var : toKeepUpdated)
    {
        try
        {
            int index = measurements_indices.at(var->addressInSimulator);
            var->data = numbers_received[index];
        }
        catch (out_of_range& err)
        {
            cerr << "server: error while attempting to update a var whose address," << endl
                 << var->addressInSimulator << ", is not in the measurements_indices map" << endl;
        }
    }

    mutex_dealing_with_the_set.unlock();
}

void FromAeroplaneServer::keepThisVarUpdated(Var *var)
{
    mutex_dealing_with_the_set.lock();
    toKeepUpdated.insert(var);
    mutex_dealing_with_the_set.unlock();
}

const std::map<std::string, int> FromAeroplaneServer::measurements_indices =
{
        {"/instrumentation/airspeed-indicator/indicated-speed-kt",        0},
        {"/sim/time/warp",                                                1},
        {"/controls/switches/magnetos",                                   2},
        {"/instrumentation/heading-indicator/offset-deg",                 3},
        {"/instrumentation/altimeter/indicated-altitude-ft",              4},
        {"/instrumentation/altimeter/pressure-alt-ft",                    5},
        {"/instrumentation/attitude-indicator/indicated-pitch-deg",       6},
        {"/instrumentation/attitude-indicator/indicated-roll-deg",        7},
        {"/instrumentation/attitude-indicator/internal-pitch-deg",        8},
        {"/instrumentation/attitude-indicator/internal-roll-deg",         9},
        {"/instrumentation/encoder/indicated-altitude-ft",                10},
        {"/instrumentation/encoder/pressure-alt-ft",                      11},
        {"/instrumentation/gps/indicated-altitude-ft",                    12},
        {"/instrumentation/gps/indicated-ground-speed-kt",                13},
        {"/instrumentation/gps/indicated-vertical-speed",                 14},
        {"/instrumentation/heading-indicator/indicated-heading-deg",      15},
        {"/instrumentation/magnetic-compass/indicated-heading-deg",       16},
        {"/instrumentation/slip-skid-ball/indicated-slip-skid",           17},
        {"/instrumentation/turn-indicator/indicated-turn-rate",           18},
        {"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 19},
        {"/controls/flight/aileron",                                      20},
        {"/controls/flight/elevator",                                     21},
        {"/controls/flight/rudder",                                       22},
        {"/controls/flight/flaps",                                        23},
        {"/controls/engines/engine/throttle",                             24},
        {"/controls/engines/current-engine/throttle",                     25},
        {"/controls/switches/master-avionics",                            26},
        {"/controls/switches/starter",                                    27},
        {"/engines/active-engine/auto-start",                             28},
        {"/controls/flight/speedbrake",                                   29},
        {"/sim/model/c172p/brake-parking",                                30},
        {"/controls/engines/engine/primer",                               31},
        {"/controls/engines/current-engine/mixture",                      32},
        {"/controls/switches/master-bat",                                 33},
        {"/controls/switches/master-alt",                                 34},
        {"/engines/engine/rpm",                                           35},
};

const int FromAeroplaneServer::num_measurements = 36;
