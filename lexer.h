//
// Created by hodyah on 15/12/2019.
//

#ifndef FLIGHT_PROJECT_LEXER_H
#define FLIGHT_PROJECT_LEXER_H
using namespace std;
#include <string>
#include <queue>
#include <fstream>
#include <unordered_map>
#include "iostream"
//#include "lexerFile.h"

/**.
 * lexer - split file string to short string.
 * lexer split accurding (), =, ->, <-,command space and tab.
 * lexer save the split string in queue on heap.
 * lexer puse =, ->, <- on the queue and not () for function (yes for mat' action),command space and tab.
 * @param fileName the file to read and split.
 */
class lexer{
    vector<string>* commandVactor;
    string currentStringInLop;
    unordered_map<vector<string>::iterator*, vector<string>::iterator*> *mapCloseBracketsIt =
            new unordered_map<vector<string>::iterator*, vector<string>::iterator*>();
    queue<vector<string>::iterator> itToBeginBracket;
public:
    lexer();
//    vector<string>* splitFile();
    void splitTheLine(string& line);
    vector<string>* getVectorLexer();
private:
    void splitAcurddingSign(string line, int i, char sign);
    void addCurrentStringToQueue();
    void addItartorToMap(char bracket);
    friend class lexerFile;
};
class NotCurrentBracketInFile: public exception{};
#endif FLIGHT_PROJECT_LEXER_H