//
// Created by hodyah on 15/12/2019.
//

#ifndef FLIGHT_PROJECT_LEXER_H
#define FLIGHT_PROJECT_LEXER_H

#include <string>
#include <queue>
#include <fstream>
#include <map>
#include "iostream"
#include "globals_singleton.h"
//#include "lexerFile.h"

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
    std::map<iter *, iter *> *mapCloseBracketsIt = new std::map<iter *, iter *>();
    std::queue<iter> itToBeginBracket; // todo לא עדיף מחסנית?
public:
//    vector<string>* splitFile();
    void splitTheLine(std::string &line);

    std::vector<std::string> *getVectorLexer();

private:
    void splitAcurddingSign(std::string line, int i, char sign);

    void addCurrentStringToQueue();

    void addItartorToMap(char bracket);

    friend class lexerFile;
};

class NotCurrentBracketInFile : std::exception {};

#endif // FLIGHT_PROJECT_LEXER_H