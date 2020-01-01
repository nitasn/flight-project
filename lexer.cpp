//
// Created by hodyah on 15/12/2019.
//
#include "lexer.h"
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
            this->commandVactor->push_back(this->currentStringInLop);
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
        this->commandVactor->push_back(currentStringInLop);
        currentStringInLop.clear();
    }
}
/**
 * split all line acuurding lexer: she put all the residue string
 * to one string and put him to the queue. if have , she split string ther.
 * @param line to split
 */
void lexer::splitTheLine(string& line){
    for(int i = 0; i != line.size(); i++) {
        if (line[i] == '('){
            addCurrentStringToQueue();
            splitAcurddingSign(line, i+1, ')');
            break;
        } else if(line[i] == '='){
            addCurrentStringToQueue();
            if (line[i+1] != '='){
                this->commandVactor->push_back("=");
                splitAcurddingSign(line, i+1, ' ');
                break;
            }
            this->commandVactor->push_back("==");
            i++;
        } else if(line[i] == ' ' || (line[i] == '\t')){
            addCurrentStringToQueue();
        } else if(line[i] == '{' || line[i] == '}'){
            addCurrentStringToQueue();
            string s;
            this->commandVactor->push_back(s + line[i]);
            addItartorToMap(line[i]);
        } else if ((line[i] == '-' && line[i+1] == '>')||(line[i] == '<' && line[i+1] == '-')
                   ||line[i]=='>' || line[i] == '<' || line[i] == '!'){
            addCurrentStringToQueue();
            string s;
            if (line[i + 1] == '-' || line[i+1] == '>' || line[i+1] == '=' ){
                this->commandVactor->push_back(s + line[i] + line[i+1]);
                i++;
            }else{
                this->commandVactor->push_back(s + line[i]);
            }
        }else {
            currentStringInLop = currentStringInLop + "" + line[i];
        }
    }
}
/**
 * @return vector of split input
 */
vector<string>* lexer:: getVectorLexer(){
    return this->commandVactor;
}

/**ToAeroplaneClientSingleton
 * add itartor to map bracket itartor
 * @param bracket char, can be { or }.
 */
void lexer:: addItartorToMap(char bracket){
    if(bracket == '{'){
        this->itToBeginBracket.push((--this->commandVactor->end()));
    } else{
        try{
            this->mapCloseBracketsIt->insert(make_pair(&this->itToBeginBracket.front(),
                                                         &(--this->commandVactor->end())));
            this->itToBeginBracket.pop();
        }catch (...){throw NotCurrentBracketInFile();}
    }
}



