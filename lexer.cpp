//
// Created by hodyah on 15/12/2019.
//

#include "lexer.h"
#include "iostream"
#include <fstream>

class lexer:: lexer(string fileName){
ifstream insertFile(fileName, ios::in);
if (insertFile.fail() || insertFile.bad()){
throw "error. not have this page";
}

};
