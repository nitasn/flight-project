//
// Created by hodyah on 15/12/2019.
//


using namespace std;
#ifndef UNTITLED7_LEXER_H
#define UNTITLED7_LEXER_H
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
    unordered_map<vector<string>::iterator*, vector<string>::iterator*> mapCloseBracketsIt;
    queue<vector<string>::iterator> itToBeginBracket;
public:
    lexer();
//    vector<string>* splitFile();
    void splitTheLine(string& line);
    vector<string>::iterator getMatchingParen(vector<string>::iterator paren);
    vector<string>* getVectorLexer();
private:
    void splitAcurddingSign(string line, int i, char sign);
    void addCurrentStringToQueue();
    void addItartorToMap(char bracket);
    friend class lexerFile;
};
class NotHaveThisItartorInMapBrackets: public exception{};
class NotCurrentBracketInFile: public exception{};
#endif //UNTITLED7_LEXER_H