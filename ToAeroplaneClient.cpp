#include "ToAeroplaneClient.h"
#include <sstream>

using namespace std;

void ToAeroplaneClient::send_var_to_aeroplane(Var &var)
{
    stringstream ss;
    ss << "set " << var.addressInSimulator << " " << var.data << "\r\n";
    string s = ss.str();

    TelnetClient::send_message(s.c_str(), s.size());
}
