#include "controlFly.h"

using namespace std;

struct Var {
    double data;
    string addressInSimulator;
};

class Server {
    unordered_set<string>
};

unordered_map<string, Var> variables;

//template<class T> class Singleton {
//    T *t = nullptr;
//
//public:
//    T* getIt()
//    {
//        if (t == nullptr)
//            t = new T;
//        return t;
//    }
//};

void ifCommand(vector<string>::iterator& begin)
{
}


void printCommand(vector<string>::iterator& begin)
{
}

void var

unordered_map<string, function<void(vector<string>::iterator& begin)>> mapCommandFunctions = {
        {"if", ifCommand},
        {"print", printCommand}
};

void parse(vector<string>::iterator& begin, vector<string>::iterator& end)
{
    for (auto iter = begin; iter != end; iter++)
    {
        if (mapCommandFunctions.find(*iter) != mapCommandFunctions.end())
        {
            auto func = mapCommandFunctions[*iter];
            func(++iter);
        } else
        {
            // x = 0
        }
    }
}