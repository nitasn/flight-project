//
// Created by hodyah on 30/12/2019.
//

#ifndef FLIGHT_PROJECT_LEXERFILE_H
#define FLIGHT_PROJECT_LEXERFILE_H

#include "lexer.h"

class lexerFile : public lexer
{
    std::ifstream insertFile;

public:
    explicit lexerFile(std::string &fileName);

    std::vector<std::string> *splitFile();
};

#endif // FLIGHT_PROJECT_LEXERFILE_H
