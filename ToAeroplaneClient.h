//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#ifndef FLIGHT_PROJECT_TOAEROPLANECLIENT_H
#define FLIGHT_PROJECT_TOAEROPLANECLIENT_H

#include <map>
#include "TelnetClient.h"
#include "var.h"

class ToAeroplaneClient : TelnetClient
{
public:
    /// may throw TelnetClient::CouldNotConnectToServer
    explicit ToAeroplaneClient(int port) : TelnetClient(port) { }

    void send_var_to_aeroplane(std::string& varName);
};


#endif // FLIGHT_PROJECT_TOAEROPLANECLIENT_H
