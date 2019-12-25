//
// Created by hodyah on 15/12/2019.
//

#include "lexer.h"
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
queue<string>* lexer::splitFile(){
    string line{};
    while(!insertFile.eof()){
        getline(insertFile, line);
        for(int i = 0; i != line.size(); i++) {
            if (line[i] == '('){
                addCurrentStringToQueue();
                splitAcurddingSign(line, i+1, ')');
                break;
            } else if(line[i] == '='){
                addCurrentStringToQueue();
                if (line[i+1] != '='){
                    this->commandQueue->push("=");
                    splitAcurddingSign(line, i+1, ' ');
                    break;
                }
                this->commandQueue->push("==");
                i++;
            } else if(line[i] == ' ' || (line[i] == '\t')){
                addCurrentStringToQueue();
            } else if(line[i] == '{' || line[i] == '}'){
                addCurrentStringToQueue();
                string s;
                this->commandQueue->push(s + line[i]);
            } else if ((line[i] == '-' && line[i+1] == '>')||(line[i] == '<' && line[i+1] == '-')
                ||line[i]=='>' || line[i] == '<' || line[i] == '!'){
                addCurrentStringToQueue();
                string s;
                if (line[i + 1] == '-' || line[i+1] == '>' || line[i+1] == '=' ){
                    this->commandQueue->push(s + line[i] + line[i+1]);
                    i++;
                }else{
                    this->commandQueue->push(s + line[i]);
                }
            }else {
                currentStringInLop = currentStringInLop + "" + line[i];
            }
        }
    }
    this->insertFile.close();
    return this->commandQueue;
}
/**
 * splitAcurddingSign helping method. she put all the residue string
 * to one string and put him to the queue. if have , she split string ther.
 * @param line the string of line
 * @param i index beginning residue string
 * @param sign if need to  stop befor end line.
 */
void lexer:: splitAcurddingSign(string line, int i, char sign){
    bool flagThisIsInString = false;
    while(true){
        if((line.size() == i + 1) || line.size() == i){
            if (sign == ')' || (line.size() == i)){
                break;
            }
        }
        if(line[i] == ','){
            this->commandQueue->push(this->currentStringInLop);
            this->currentStringInLop.clear();
        } else if (((flagThisIsInString) && line[i] == ' ')|| (line[i] != ' ' && line[i] != '\t')){
            this->currentStringInLop = this->currentStringInLop + "" + line[i];
            if(line[i] == '"'){
                flagThisIsInString = !flagThisIsInString;
            }
        }
        i++;
    }
    addCurrentStringToQueue();
}
/**
 * add the string to queue if he not empty
 */
void lexer:: addCurrentStringToQueue(){
    if(!currentStringInLop.empty()){
        this->commandQueue->push(currentStringInLop);
        currentStringInLop.clear();
    }
}