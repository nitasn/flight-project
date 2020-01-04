#ifndef FLIGHT_PROJECT_TELNETSERVER_H
#define FLIGHT_PROJECT_TELNETSERVER_H

#include <thread>
#include <map>
#include <set>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

#define MAX_CONNECTIONS 1

class TelnetServer
{
    virtual void process_data(const char *buffer, int buffer_size) = 0; // to separate data-reading and data-processing

    int port;
    int socket_fd{};
    int client_socket{}; // expecting one client only

    /// call 'process_data' whenever new data is received
    static void mainloop(TelnetServer *self);

    /// if changed to true, mainloop_thread will terminate
    bool should_terminate = false;

    std::thread *mainloop_thread = nullptr;

public:
    void run();

    explicit TelnetServer(int portNum) : port(portNum){}

    virtual ~TelnetServer();


    class ServerError_AcceptingClientFailed  : std::exception{};

    class ServerError_CouldNotBindSocketToIP : std::exception{};

    class ServerError_CouldNotCreateSocket   : std::exception{};

    class ServerError_CouldNotStartListening : std::exception{};
};


#endif // FLIGHT_PROJECT_TELNETSERVER_H
