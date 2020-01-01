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
    bool is_alive;
    /// call 'process_data' whenever new data is received
    static void mainloop(TelnetServer *self);
public:
    void run() { std::thread(mainloop, this).detach(); }
    explicit TelnetServer(int portNum) : port(portNum) { is_alive = false; }
    virtual ~TelnetServer() { kill(); }
    void kill() { is_alive = false; } // todo i dont think kill works while server waits for client
    bool isAlive() { return is_alive; }

    class serverNetworkError : exception {};
};


#endif FLIGHT_PROJECT_TELNETSERVER_H
