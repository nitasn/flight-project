//
// Created by hodyah on 19/12/2019.
//
//TODO ש כאן טיפול לא נכון בשגיאות - צריך לחזור לזה
#include <unordered_map>
#include "server.h"
#include "stringsplit.cpp"
/**.
 * server create server to contact the fly.
 * @param portNum the port num to clint
 */
server::server() {

}

void f() {
    cout << "hey gf" << endl;
}

void server:: openTheServer(int portNum){
    restartAddres(portNum);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return;
    }
    if (listen(socketfd, MAX_CONNECTIONS) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        return;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }
    thread readingClient(informationFromServer, this->socketfd, this->address);
    readingClient.join();
}
/**.td::
 *informationFromServer update all time with thread the information
 * that clion send
 * @param socketfd
 * @param address
 * @param buffer
 */
void informationFromServer(int socketfd, sockaddr_in address,
        unordered_map<string, pair<string, double>>* variableStringAndValue,
                           unordered_map<string, int> aPlaceMap){
    while (true){
        char buffer[1024];
        int client_socket = accept(socketfd, (struct sockaddr *)&address,
                                   (socklen_t*)&address);
        if (client_socket == -1) {
            std::cerr<<"Error accepting client"<<std::endl;
            return;
        }
        int valread = read( client_socket , buffer, 1024);
        cout<<buffer<<endl;
        cout << "server just read " << buffer << endl;
        upDateDictenaryVariable(buffer,variableStringAndValue,aPlaceMap);
    }
}
/**
 * informationFromServer
 * reset the adrees and socket of clion
 * @param portNum clion port num
 */
void server:: restartAddres(int portNum){
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        std::cerr << "problem with open socket. semothing not work"<< endl;
        throw (exception());
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portNum);
}
/**
 * update all the variable in map variables accurding string value from fly
 * @param buffer the string that send from the fly
 * @param variableStringAndValue map of all the variables that the plan need
 * @param aPlaceMap map of place in string buffer
 */
void upDateDictenaryVariable(char* buffer,unordered_map<string, pair<string, double>>* variableStringAndValue,
        unordered_map<string, int> aPlaceMap){
//    auto itRunOnMap = variableStringAndValue->begin();
//    strings_array *stringsBuffer = split(buffer, ',');
//    for(; itRunOnMap!= variableStringAndValue->end(); itRunOnMap++){
//        pair<string, double> pairNewObject(itRunOnMap->second.first,
//                atof(stringsBuffer->arr[aPlaceMap[itRunOnMap->second.first]].c_str()));
//        auto newPair = make_pair(itRunOnMap->first, pairNewObject);
//        (variableStringAndValue)->insert(newPair);
//    }
//    delete stringsBuffer;
}