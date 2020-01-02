#include "ToAeroplaneClient.h"
#include "globals_singleton.h"
#include <sstream>

void ToAeroplaneClient::send_var_to_aeroplane(std::string &varName)
{
    string s;

    app::globals->do_with_vars_map([&]()
    {
        map<string, Var *> &vars = *app::globals->varsMap;

        stringstream ss;
        ss << "set " << vars[varName]->addressInSimulator << " " << vars[varName]->data << "\r\n";
        s = ss.str();
    });

    TelnetClient::send_message(s.c_str(), s.size());
}
