//
// Created by hodyah on 15/12/2019.
//

#include "lexer.h"
#include "iostream"
#include <queue>
/**.
 * lexer - split file string to short string.
 * lexer split accurding (), =, ->, <-,command space and tab.
 * lexer save the split string in queue on heap.
 * lexer puse =, ->, <- on the queue and not () for function (yes for mat' action),command space and tab.
 * @param fileName the file to read and split.
 */
lexer::lexer(string fileName){
    this->commandQueue = new queue<string>();
    this->insertFile.open(fileName, ios::in);
    if (insertFile.fail() || insertFile.bad()){
        throw "error. not have this page";
    }
};
/**.
 * splitFile methot split the file.
 */
void lexer::splitFile(){
    string line{};
    while(!insertFile.eof()){
        getline(insertFile, line);
        string currentStringInLop;
        for(int i = 0; i != line.size(); i++) {
            if (line[i] == '('){
                if(!currentStringInLop.empty()){
                    this->commandQueue->push(currentStringInLop);
                    currentStringInLop.clear();
                }
                splitAcurddingSign(line, i+1, ')');
                break;
            } else if(line[i] == '='){
                if(!currentStringInLop.empty()){
                    this->commandQueue->push(currentStringInLop);
                    currentStringInLop.clear();
                }
                this->commandQueue->push("=");
                splitAcurddingSign(line, i+1, ' ');
                break;
            } else if(line[i] == ' ' || (line[i] == '\t')){
                if(!currentStringInLop.empty()){
                    this->commandQueue->push(currentStringInLop);
                    currentStringInLop.clear();
                }
            } else if ((line[i] == '-' && line[i+1] == '>')||(line[i] == '<' && line[i+1] == '-')){
                if (!currentStringInLop.empty()){
                    this->commandQueue->push(currentStringInLop);
                    currentStringInLop.clear();
                }
                if (line[i] == '-'){
                    this->commandQueue->push("->");
                }else{
                    this->commandQueue->push("<-");
                }
                i++;
            }else {
                currentStringInLop = currentStringInLop + "" + line[i];
            }
        }
    }
}
/**
 * splitAcurddingSign helping method. she put all the residue string
 * to one string and put him to the queue. if have , she split string ther.
 * @param line the string of line
 * @param i index beginning residue string
 * @param sign if need to  stop befor end line.
 */
void lexer:: splitAcurddingSign(string line, int i, char sign){
    string inputCommand;
    while(true){
        if((line.size() == i + 1) || line.size() == i){
            if (sign == ')' || (line.size() == i)){
                break;
            }
        }
        if(line[i] == ','){
            this->commandQueue->push(inputCommand);
            inputCommand.clear();
        } else if (line[i] != ' ' && line[i] != '\t'){
            inputCommand = inputCommand + "" + line[i];
        }
        i++;
    }
    if(!inputCommand.empty()){
        this->commandQueue->push(inputCommand);
        inputCommand.clear();
    }
}
/**.
 * return queue split lexer.
 * @return
 */
queue<string>* lexer:: returnSplitFileQueue(){
    return this->commandQueue;
}