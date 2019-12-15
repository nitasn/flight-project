//
// Created by hodyah on 15/12/2019.
//

#include "lexer.h"
#include "iostream"
#include <fstream>
#include <queue>

lexer::lexer(string fileName){
    this->commandQueue = new queue<string>();
    ifstream insertFile(fileName, ios::in);
    if (insertFile.fail() || insertFile.bad()){
        throw "error. not have this page";
    }
    string line{};
    while(!insertFile.eof()){
        getline(insertFile, line);
        string currentStringInLop;
        for(int i = 0; line[i] != '/n'; i++) {
            if (line[i] == '('){

            } else if(line[i] == '='){

            } else if(line[i] == ' '){
                // לבדוק מילים שמורות
                // לבדוק משתנים קיימים
                // אם לא זה ולא זה - להמשיך הלאה
            } else if (line[i] == '-' && line[i+1] == '>'){

            } else if (line[i] == '<' && line[i+1] == '-'){

            }else if(line[i]){
                currentStringInLop = currentStringInLop + "" + line[i];
            }

        // ביטוייים שמתחילים במילים שמורות
        // ביטויים שמתחילים בפונקציה
        // השמה של משתנים
        }

    }
};
