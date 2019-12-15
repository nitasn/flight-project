//
// Created by hodyah on 15/12/2019.
//
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <queue>
#include "Expression.h"

using namespace std;
#ifndef UNTITLED7_LEXER_H
#define UNTITLED7_LEXER_H
class lexer{
public:lexer(string fileName);
    queue<string> *commandQueue;
};

#endif //UNTITLED7_LEXER_H