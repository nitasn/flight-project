//
// Created by hodyah on 19/12/2019.
//

#include "connectControlClient.h"
#include "server.h"

/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 */
connectControlClient:: connectControlClient(): command(){
};
void connectControlClient:: execut(queue<string>* inputQueue){
    try{
        server serverOpen(atof((inputQueue->front().c_str())));
        inputQueue->pop();
    } catch (...) {
        return;
    }
}