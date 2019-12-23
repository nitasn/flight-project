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
#include "stringsplit.cpp"
/**.
 * server create server to contact the fly.
 * @param portNum the port num to clint
 */
void informationFromServer(int socketfd, sockaddr_in address);
void upDateDictenaryVariable(char* buffer,
        unordered_map<string, pair<string, double>>* variableStringAndValue,
                             unordered_map<string, int> aPlaceMap);
class server{
    int socketfd;
    sockaddr_in address;
    const int MAX_CONNECTIONS = 5;
public:server();
    void openTheServer(int portNum);
    void restartAddres(int portNum);
};
#endif //FLIGHT_PROJECT_SERVER_H
