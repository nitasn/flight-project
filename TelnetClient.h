#ifndef TESTION_TELNETCLIENT_H
#define TESTION_TELNETCLIENT_H

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TelnetClient
{
    int client_socket{};
    bool connect_to_server(int port);

public:
    class CouldNotConnectToServer : std::exception {};
    explicit TelnetClient(int port)
    {
        if (!connect_to_server(port)) throw CouldNotConnectToServer();
    }

    void send_message(const char *buffer, int buffer_size);
    ~TelnetClient() { close(client_socket); }
};

#endif //TESTION_TELNETCLIENT_H
