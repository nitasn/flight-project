//
// Created by hodyah on 15/12/2019.
//
#include "lexer.h"

using namespace std;

/**
 * splitAccordingToSign helping method. she put all the residue string
 * to one string and put him to the queue. if have , she split string ther.
 * @param line the string of line
 * @param i index beginning residue string
 * @param sign if need to  stop befor end line.
 */
void lexer:: splitAccordingToSign(string line, size_t& i, char sign){
    bool flagThisIsInString = false;
    while(true){
        if(((line.size() == i + 1) || line.size() == i) || ((sign == ')') && (line[i] == ')'))){
            if ((sign == ')') || (line.size() == i)){
                if(line[i] == ')'){
                    i++;
                }
                break;
            }
        }
        if(line[i] == '{' || line[i] == '}') { //if this block
            addCurrentStringToQueue();
            string s;
            this->commandVector->push_back(s + line[i]);
            addItartorToMap(line[i]);
            i++;
            return;
        }
        if(line[i] == ','){
            this->commandVector->push_back(this->currentStringInLop);
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
    --i;
}
/**
 * add the string to queue if he not empty
 */
void lexer:: addCurrentStringToQueue(){
    if(!currentStringInLop.empty()){
        this->commandVector->push_back(currentStringInLop);
        currentStringInLop.clear();
    }
}
/**
 * split all line acuurding lexer: she put all the residue string
 * to one string and put him to the queue. if have , she split string ther.
 * @param line to split
 */
void lexer::splitTheLine(string& line){
    for(size_t i = 0; i != line.size(); i++) {
        if (checkIfThisCondition(line)){return;}
        if (line[i] == '('){ //if this is string between braect, split him and break
            addCurrentStringToQueue();
            splitAccordingToSign(line, ++i, ')');
            break;
        } else if(line[i] == '='){ // if = this is name = somthing, not need split him like hir
            addCurrentStringToQueue();
            this->commandVector->push_back("=");
            splitAccordingToSign(line, ++i, ' ');
            break;
        } else if(line[i] == ' ' || (line[i] == '\t')){ // ignor space and tab
            addCurrentStringToQueue();
        } else if(line[i] == '{' || line[i] == '}'){ //if this block
            addCurrentStringToQueue();
            string s;
            this->commandVector->push_back(s + line[i]);
            addItartorToMap(line[i]);
        } else if ((line[i] == '-' && line[i+1] == '>')||(line[i] == '<' && line[i+1] == '-')){ //new var
            addCurrentStringToQueue();
            string s;
            this->commandVector->push_back(s + line[i] + line[i + 1]);
            i++;
        }else { // add the char to string
            currentStringInLop = currentStringInLop + "" + line[i];
        }
    }
}
/**
 * checkIfThisCondition check if the line is condition. if true, split to four part:
 * the condition command, the condition left expression, the opertor condition and
 * the right condition expression. return true if  this condition, or false else.
 * @param line the string to check
 * @return true if  this condition, or false else
 */
bool lexer::checkIfThisCondition(string& line){
    if(line.find("while") == string::npos && line.find("While") == string::npos &&
            line.find("if") == string::npos && line.find("If") == string::npos){ //this not condition
        return false;
    }
    size_t i = 0;
    while(line[i] != ' ' || this->currentStringInLop.empty()){ // take the condition cocmmand
        if (line[i] != '\t' && line[i] != ' '){
            this->currentStringInLop += line[i]; }
        i++;
    }
    addCurrentStringToQueue();
    while (line[i] != '=' && line[i] != '>' && line[i] != '<' && line[i] != '!'){
        if (line[i] != ' ' && line[i] != '\t'){ this->currentStringInLop += line[i];} // left expression
        i++;
    }
    addCurrentStringToQueue();
    string s;
    if(line[i + 1] == '='){
        this->commandVector->push_back(s + line[i] + line[i+1]);
        i++;
    } else{
        this->commandVector->push_back(s + line[i]);
    }
    splitAccordingToSign(line, ++i, ' '); // right condition
    return true;
}

/**
 * ToAeroplaneClientSingleton add itartor to map bracket itartor
 * @param bracket char, can be { or }.
 */
void lexer:: addItartorToMap(char bracket){
    if(bracket == '{'){
        this->itToBeginBracket.push((--this->commandVector->end()));
    } else{
        try{
            app::globals->matching_curly_brackets->insert(make_pair(this->itToBeginBracket.top(),
                                                         (--this->commandVector->end())));
            this->itToBeginBracket.pop();
        }catch (...){throw NotCurrentBracketInFile();}
    }
}



