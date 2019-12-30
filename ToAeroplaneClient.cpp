#include "ToAeroplaneClient.h"
#include "singltonGlobals.h"
#include <sstream>

void ToAeroplaneClient::send_var_to_aeroplane(std::string &varName)
{
    VarsMap::mutexSingleton.it->lock();

    map<string, Var *> &vars = VarsMap::mapSingleton::it;

    stringstream ss;
    ss << "set " << vars[varName]->addressInSimulator << " " << vars[varName]->data << "\r\n";
    string s = ss.str();

    VarsMap::mutexSingleton.it->unlock();

    TelnetClient::send_message(s.c_str(), s.size());
}
