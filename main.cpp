//
// Created by Nitsan BenHanoch on 15/12/2019.
//

#include "lexer.h"
#include "controlFly.h"

using namespace std;

int main(int a, char *arg[])
{
//    {// בדיקה והדגמה איך הלאקסר מפרק את הקובץ
//        lexer a("/home/hodyah/CLionProjects/flight-project/fly.txt");
//        a.splitFile();
//        queue<string> *b = a.returnSplitFileQueue();
//        while (!b->empty()) {
//            cout << b->front() << endl;
//            b->pop();
//        }
//    }// סוף בדיקת לאקסר
    controlFly control;
    control.playControlFly(arg[1]);
}