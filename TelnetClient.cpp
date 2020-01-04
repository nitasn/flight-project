//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#include "TelnetClient.h"
#include "globals_singleton.h"

void TelnetClient::send_message(const char *buffer, int buffer_size)
{
    if (send(client_socket, buffer, buffer_size, 0) == -1)
    {
        std::cerr << "client error - could not send: " << std::string(buffer, buffer_size) << std::endl;
        return;
    }

    if (app::globals->verbose)
    {
        std::cout << "client successfully sent: " << std::string(buffer, buffer_size) << std::endl;
    }
}

bool TelnetClient::connect_to_server(int port)
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        std::cerr << "Could not create a socket" << std::endl;
        return false;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address{}; //it means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host
    if (connect(client_socket, (struct sockaddr *) &address, sizeof(address)) == -1)
    {
        std::cerr << "Could not connect to host server" << std::endl;
        return false;
    }
    if (app::globals->verbose)
    {
        std::cout << "Client is now connected to server" << std::endl;
    }
    return true;
}