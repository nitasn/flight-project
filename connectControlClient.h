//
// Created by hodyah on 19/12/2019.
//

#ifndef FLIGHT_PROJECT_CONNECTCONTROLCLIENT_H
#define FLIGHT_PROJECT_CONNECTCONTROLCLIENT_H
#include "command.h"
/**.
 * connectControlClient connect to control client with the
 * current input and update thr queue
 */
class connectControlClient: public command{
public:
    connectControlClient();
    void execut(queue<string>* inputQueue);
};
#endif //FLIGHT_PROJECT_CONNECTCONTROLCLIENT_H
