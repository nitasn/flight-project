//
// Created by hodyah on 19/12/2019.
//
#ifndef FLIGHT_PROJECT_SERVER_H
#define FLIGHT_PROJECT_SERVER_H

using namespace std;
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include "thread"
void  informationFromServer(int socketfd, sockaddr_in address,char* buffer);
class server{
    int socketfd;
    sockaddr_in address;
    char buffer[1024];
public:server();
    int OpenServerCommand(int portNum);
    void restartAddres(int portNum);
};
#endif //FLIGHT_PROJECT_SERVER_H