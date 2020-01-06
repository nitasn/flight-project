//
// Created by Nitsan BenHanoch on 28/12/2019.
//

#include "TelnetServer.h"
#include "globals_singleton.h"

/**
 * mainloop accept to client (simulatur) and update in thread all 10 second
 * the information in him buffer accurding what the simulatur send
 * @param self the server
 */
void TelnetServer::mainloop(TelnetServer *self) // creating a method out of a static function in the pythonic way
{
    char buffer[1024] = {0};
    int msg_length;

    while (!self->should_terminate)
    {
        msg_length = read(self->client_socket, buffer, 1024);

        if (msg_length > 0 && !self->should_terminate) // could be changed to true from main thread
        {
            self->process_data(buffer, msg_length);
        }
        else break;
    }
}
/**
 * run open the server and try to connect to the simulatur. in block until connected
 */
void TelnetServer::run()
{
    socket_fd = socket(AF_INET, SOCK_STREAM, 0); //create socket
    if (socket_fd == -1)
    {
        std::cerr << "Could not create a socket" << std::endl;
        throw ServerError_CouldNotCreateSocket();
    }
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(socket_fd, (struct sockaddr *) &address, sizeof(address)) == -1)
    {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        throw ServerError_CouldNotBindSocketToIP();
    }
    if (listen(socket_fd, MAX_CONNECTIONS) == -1)
    {
        std::cerr << "Error during listening command" << std::endl;
        throw ServerError_CouldNotStartListening();
    }
    if (app::globals->verbose)
    {
        std::cout << "server is now listening..." << std::endl;
    }
    client_socket = accept(socket_fd, (struct sockaddr *) &address, (socklen_t *) &address); // blocking!

    if (client_socket == -1)
    {
        std::cerr << "server: error accepting client" << std::endl;
        throw ServerError_AcceptingClientFailed();
    }
    if (app::globals->verbose)
    {
        std::cout << "server accepted client... server starts mainloop" << std::endl;
    }

    mainloop_thread = new std::thread(mainloop, this);
}
/**
 * close the socket, stop the thread and delete what need
 */
TelnetServer::~TelnetServer()
{
    should_terminate = true;
    mainloop_thread->join();
    delete mainloop_thread;

    close(socket_fd); // closing the listening socket
    close(client_socket);
}

