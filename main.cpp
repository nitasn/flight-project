//
// Created by Nitsan BenHanoch on 15/12/2019.
//

#include "lexer.h"
//#include "controlFly.h"
//#include "server.h"

using namespace std;

int main(int argc, char *argv[])
{
    {// בדיקה והדגמה איך הלאקסר מפרק את הקובץ
        lexer a("/home/hodyah/CLionProjects/flight-project/fly.txt");
        queue<string> *b =         a.splitFile();
        while (!b->empty()) {
            cout << b->front() << endl;
            b->pop();
        }
    }// סוף בדיקת לאקסר
//    controlFly control;
//    control.playControlFly(arg[1]);
//    server s;
//    s.openTheServer(5400);
}