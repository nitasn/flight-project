//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#include "TelnetServer.h"

void TelnetServer::mainloop(TelnetServer *self) // creating a method out of a static function in the pythonic way
{
    self->is_alive = true;
    self->socket_fd = socket(AF_INET, SOCK_STREAM, 0); //create socket
    if (self->socket_fd == -1)
    {
        std::cerr << "Could not create a socket" << std::endl;
        self->is_alive = false;
        throw serverNetworkError();
    }
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(self->port);
    if (bind(self->socket_fd, (struct sockaddr *) &address, sizeof(address)) == -1)
    {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        self->is_alive = false;
        throw serverNetworkError();
    }
    if (listen(self->socket_fd, MAX_CONNECTIONS) == -1)
    {
        std::cerr << "Error during listening command" << std::endl;
        self->is_alive = false;
        throw serverNetworkError();
    }
    std::cout << "Server is now listening..." << std::endl;
    self->client_socket = accept(self->socket_fd, (struct sockaddr *) &address, (socklen_t *) &address);
    // todo if "kill" called - stop waiting for the client!
    if (self->client_socket == -1)
    {
        std::cerr << "Error accepting client" << std::endl;
        self->is_alive = false;
        throw serverNetworkError();
    }
    std::cout << "Server accepted client..." << std::endl;
    char buffer[1024] = {0};
    int msg_length;
    while (self->is_alive) // note: this variable may be changed from a different thread, using the function "kill"
    {
        msg_length = read(self->client_socket, buffer, 1024);
        if (msg_length > 0)
        {
            self->process_data(buffer, msg_length);
        }
        else
        {
            self->is_alive = false; // but we too can kill ourselves
            // todo is it right to kill ourselves as a server if msg sent to us has a length of 0?
        }
    }
    close(self->socket_fd); // closing the listening socket
    // close(self->client_socket); // todo is this needed?
}