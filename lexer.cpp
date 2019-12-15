//
// Created by hodyah on 15/12/2019.
//

#include "lexer.h"
#include "iostream"
#include <fstream>
#include <queue>

class lexer:: lexer(string fileName){
    this->commandQueue = new queue<string>();
    ifstream insertFile(fileName, ios::in);
    if (insertFile.fail() || insertFile.bad()){
        throw "error. not have this page";
    }
    string line{};
    while(!insertFile.eof){
        getline(insertFile, line);
        char runCharOnLine;
        string currentStringInLop;
        while(runCharOnLine != '/n'){
            if(runCharOnLine!= ' ' && runCharOnLine != '(' && runCharOnLine != '')
        }
    }
};
