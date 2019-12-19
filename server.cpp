//
// Created by hodyah on 19/12/2019.
//

#include "server.h"

server::server() {
}
int server:: OpenServerCommand(int portNum){
    restartAddres(portNum);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -3;
    }
    if (listen(socketfd, 5) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        return -4;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }
    std::thread readingCilion(informationFromServer, this->socketfd, this->address, this->buffer);
    readingCilion.join();
}
void informationFromServer(int socketfd, sockaddr_in address,char* buffer){
    while (true){
        int client_socket = accept(socketfd, (struct sockaddr *)&address,
                                   (socklen_t*)&address);
        if (client_socket == -1) {
            std::cerr<<"Error accepting client"<<std::endl;
            return;
        }
        int valread = read( client_socket , buffer, 1024);
        std::cout<<buffer<<std::endl;
    }
}

void server:: restartAddres(int portNum){
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        std::cerr << "problem with open socket. semothing not work"<< endl;
        throw (new exception());
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portNum);
}