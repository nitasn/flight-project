//
// Created by hodyah on 15/12/2019.
//

#ifndef FLIGHT_PROJECT_LEXER_H
#define FLIGHT_PROJECT_LEXER_H

#include <string>
#include <stack>
#include <fstream>
#include <map>
#include "iostream"
#include "globals_singleton.h"

/**.
 * lexer - split file string to short string.
 * lexer split accurding (), =, ->, <-,command space and tab.
 * lexer save the split string in queue on heap.
 * lexer puse =, ->, <- on the queue and not () for function (yes for mat' action),command space and tab.
 * @param fileName the file to read and split.
 */
class lexer
{
    std::vector<std::string> *commandVector;
    std::string currentStringInLop;
    std::stack<iter> itToBeginBracket;
public:
    void splitTheLine(std::string &line);

//    std::vector<std::string> *getVectorLexer();

private:
    void splitAccordingToSign(std::string line, size_t& i, char sign);

    void addCurrentStringToQueue();

    void addItartorToMap(char bracket);
    bool checkIfThisCondition(std::string& line);

    friend class lexerFile;
};
/**
 * error if the bracket not current
 */
class NotCurrentBracketInFile : std::exception {};

#endif // FLIGHT_PROJECT_LEXER_H