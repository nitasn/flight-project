//
// Created by hodyah on 30/12/2019.
//

#ifndef FLIGHT_PROJECT_GLOBALS_SINGLETON_H
#define FLIGHT_PROJECT_GLOBALS_SINGLETON_H

#include "ToAeroplaneClient.h"
#include "FromAeroplaneServer.h"

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string>::iterator iter;

class app  // זה הסינגלטון היחיד שלנו!
{

public:

    static app * globals;

    /**if this true, print information on what happend in code*/
    bool verbose = false;

    ToAeroplaneClient * client = nullptr;

    FromAeroplaneServer * server = nullptr;

    std::map<std::string, Var *> * varsMap = new std::map<std::string, Var *>;

    /** map bracket block in the vector text*/
    std::map<iter, iter> * matching_curly_brackets = new std::map<iter, iter>;


     /** play mutex on var map befor function and unlock him after she finised*/
    template <typename Func> void do_with_vars_map(Func f)
    {
        varsMapMutex.lock();

        f();

        varsMapMutex.unlock();
    }

    friend int main(int, char**); // main need create discractor and undiscractor

private:

    app() = default; // dont do nothing, just main can call him

    ~app() //private, just main can call him
    {
        delete client;
        delete server;
        delete matching_curly_brackets;

        do_with_vars_map([&]()
        {
            for (auto &str_var_pair : *varsMap)

                delete str_var_pair.second; // delete all var pointers from varsMap

        });

        delete varsMap; // then delete the dict itself
    }

    std::mutex varsMapMutex;
};

#endif //FLIGHT_PROJECT_GLOBALS_SINGLETON_H