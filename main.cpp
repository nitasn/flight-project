//
// Created by Nitsan BenHanoch on 15/12/2019.
//

#include <iostream>
#include "lexer.h";

using namespace std;

int main()
{
    {// בדיקה והדגמה איך הלאקסר מפרק את הקובץ
        lexer a("/home/hodyah/CLionProjects/flight-project/fly.txt");
        a.splitFile();
        queue<string> *b = a.commandQueue;
        while (!b->empty()) {
            cout << b->front() << endl;
            b->pop();
        }
    }// סוף בדיקת לאקסר

}