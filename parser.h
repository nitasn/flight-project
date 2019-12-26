//
// Created by hodyah on 26/12/2019.
//

#ifndef FLIGHT_PROJECT_PARSER_H
#define FLIGHT_PROJECT_PARSER_H

#include "simpleCommandFromFileToMap.h"
#include "ifWhileCommandFromFileToMap.h"

class parser {
    vector<string>* commandVector;
    unordered_map<string, command*> commandMap;
public:
    parser(unordered_map<string, command *> commandMap);
    void playParser(vector<string>::iterator* runOnVector);
};


#endif //FLIGHT_PROJECT_PARSER_H
