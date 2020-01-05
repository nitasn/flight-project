//
// Created by hodyah on 30/12/2019.
//
#include "lexerFile.h"
#include "globals_singleton.h"

using namespace std;

 /**
  * lexerFile open the file accurding input string
  * trhow error if not have file
  * @param fileName name of file
  */
lexerFile::lexerFile(string& fileName){
    this->commandVector = new vector<string>();
    this->insertFile.open(fileName, ios::in);
    if (this->insertFile.fail() || this->insertFile.bad()){
        throw "error. not have this page";
    }
}
/**.
 * splitFile method split the file with lexer method
 * run on file and send all line to lexer split
 * @return vector with all command
 */
vector<string>* lexerFile::splitFile(){
    string line{};
    while(!insertFile.eof()){
        getline(insertFile, line);
        splitTheLine(line);
    }
    this->insertFile.close();
//    environment->matching_curly_brackets = this->mapCloseBracketsIt; // todo this line
    return this->commandVector;
}
