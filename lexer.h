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
using namespace std;

/**.
 * lexer - split file string to short string.
 * lexer split accurding (), =, ->, <-,command space and tab.
 * lexer save the split string in queue on heap.
 * lexer puse =, ->, <- on the queue and not () for function (yes for mat' action),command space and tab.
 * @param fileName the file to read and split.
 */
class lexer{
    vector<string>* commandVector;
    string currentStringInLop;
    map<iter*, iter*> *mapCloseBracketsIt = new map<iter*, iter*>();
    queue<iter> itToBeginBracket; // todo doesn't it have to be a stack?
public:
//    vector<string>* splitFile();
    void splitTheLine(string& line);
    vector<string>* getVectorLexer();
private:
    void splitAcurddingSign(string line, int i, char sign);
    void addCurrentStringToQueue();
    void addItartorToMap(char bracket);
    friend class lexerFile;
};
class NotCurrentBracketInFile: exception{};
#endif // FLIGHT_PROJECT_LEXER_H