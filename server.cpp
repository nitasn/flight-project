//
// Created by hodyah on 19/12/2019.
//
//TODO ש כאן טיפול לא נכון בשגיאות - צריך לחזור לזה
#include <unordered_map>
#include "server.h"
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
    thread readingClient(informationFromServer, this->socketfd, this->address, this->buffer);
    readingClient.join();
}
/**.td::
 *informationFromServer update all time with thread the information
 * that clion send
 * @param socketfd
 * @param address
 * @param buffer
 */
void informationFromServer(int socketfd, sockaddr_in address, char buffer[1024]){
    while (true){
        int client_socket = accept(socketfd, (struct sockaddr *)&address,
                                   (socklen_t*)&address);
        if (client_socket == -1) {
            std::cerr<<"Error accepting client"<<std::endl;
            return;
        }
        int valread = read( client_socket , buffer, 1024);
        std::cout<<buffer<<std::endl;
        cout << "server just read " << buffer << endl;
    }
}
/**informationFromServer
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

void upDateDictenaryVariable(char* buffer, unordered_map<string, string> a, unordered_map<string, double>* v){
    auto itRunOnMap = v->begin();
    for(; itRunOnMap!= v->end(); itRunOnMap++){
        v->at(itRunOnMap, *buffer[]);
    }
}