//
// Created by hodyah on 15/12/2019.
//
#include "lexer.h"

using namespace std;

/**
 * splitAcurddingSign helping method. she put all the residue string
 * to one string and put him to the queue. if have , she split string ther.
 * @param line the string of line
 * @param i index beginning residue string
 * @param sign if need to  stop befor end line.
 */
void lexer:: splitAcurddingSign(string line, int& i, char sign){
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
            //todo ++ or not?
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
    for(int i = 0; i != line.size(); i++) {
        if (line[i] == '('){ //if this is string between braect, split him and break
            addCurrentStringToQueue();
            splitAcurddingSign(line, ++i, ')');
            break;
        } else if(line[i] == '='){ // if = this is name = somthing, not need split him like hir
            addCurrentStringToQueue();
            if (line[i+1] != '='){
                this->commandVector->push_back("=");
                splitAcurddingSign(line, ++i, ' ');
                break;
            }
            this->commandVector->push_back("=="); // if this is condition, cuntinue split
            i++;
        } else if(line[i] == ' ' || (line[i] == '\t')){ // ignor space and tab
            addCurrentStringToQueue();
        } else if(line[i] == '{' || line[i] == '}'){ //if this block
            addCurrentStringToQueue();
            string s;
            this->commandVector->push_back(s + line[i]);
            addItartorToMap(line[i]);
        } else if ((line[i] == '-' && line[i+1] == '>')||(line[i] == '<' && line[i+1] == '-')
                   ||line[i]=='>' || line[i] == '<' || line[i] == '!'){ //condition or new var
            addCurrentStringToQueue();
            string s;
            if(line[i+1] == '='){ //if this condition opertor, need take all condition
                this->commandVector->push_back(s + line[i] + line[i + 1]);
                i++;
                splitAcurddingSign(line, ++i, ' ');
                break;
            } else if ((line[i] == '<' && line[i+1] != '-')
                       || line[i] == '>'){
                this->commandVector->push_back(s + line[i]);
                splitAcurddingSign(line,++i , ' ');
                break;
            }
            if (line[i + 1] == '-' || line[i+1] == '>' || line[i+1] == '=' ){ //condition
                this->commandVector->push_back(s + line[i] + line[i + 1]);
                i++;
            }else{ // this var
                this->commandVector->push_back(s + line[i]);
            }
        }else { // add the char to string
            currentStringInLop = currentStringInLop + "" + line[i];
        }
    }
}
///**
// * @return vector of split input
// */
//vector<string>* lexer:: getVectorLexer(){
//    return this->commandVector;
//}

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
            std::map<iter, iter> * a =  app::globals->matching_curly_brackets;
            this->itToBeginBracket.pop();
        }catch (...){throw NotCurrentBracketInFile();}
    }
}



