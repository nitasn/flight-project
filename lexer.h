//
// Created by hodyah on 15/12/2019.
//
#include <string>
#include <queue>
#include <fstream>
#include "iostream"

using namespace std;
#ifndef UNTITLED7_LEXER_H
#define UNTITLED7_LEXER_H
/**.
 * lexer - split file string to short string.
 * lexer split accurding (), =, ->, <-,command space and tab.
 * lexer save the split string in queue on heap.
 * lexer puse =, ->, <- on the queue and not () for function (yes for mat' action),command space and tab.
 * @param fileName the file to read and split.
 */
class lexer{
    queue<string> *commandQueue;
    ifstream insertFile;
    string currentStringInLop;
public:lexer(string fileName);
    queue<string>* splitFile();
private:
    void splitAcurddingSign(string line, int i, char sign);
    void addCurrentStringToQueue();
};

#endif //UNTITLED7_LEXER_H