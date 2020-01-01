//
// Created by hodyah on 30/12/2019.
//
#include "lexerFile.h"
#include "singltonGlobals.h"

/**.
 * lexer - split file string to short string.
 * lexer split accurding (), =, ->, <-,command space and tab.
 * lexer save the split string in queue on heap.
 * lexer puse =, ->, <- on the queue and not () for function (yes for mat' action),command space and tab.
 * @param fileName the file to read and split.
 */
lexerFile::lexerFile(string fileName){
    this->commandVactor = new vector<string>();
    this->insertFile.open(fileName, ios::in);
    if (this->insertFile.fail() || this->insertFile.bad()){
        throw "error. not have this page";
    }
};
/**.
 * splitFile methot split the file.
 */
vector<string>* lexerFile::splitFile(){
    string line{};
    while(!insertFile.eof()){
        getline(insertFile, line);
        splitTheLine(line);
    }
    this->insertFile.close();
    MapItToBeginBracketSingleton::it = this->mapCloseBracketsIt;
    return this->commandVactor;
}
#include "lexerFile.h"
