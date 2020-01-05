//
// Created by hodyah on 30/12/2019.
//

#ifndef FLIGHT_PROJECT_LEXERFILE_H
#define FLIGHT_PROJECT_LEXERFILE_H

#include "lexer.h"
/**.
 * lexer - split file string to short string.
 * lexer split accurding (), =, ->, <-,command space and tab.
 * lexer save the split string in queue on heap.
 * lexer puse =, ->, <- on the queue and not () for function (yes for mat' action),command space and tab.
 * @param fileName the file to read and split.
 */
class lexerFile : public lexer
{
    std::ifstream insertFile;

public:
    explicit lexerFile(std::string &fileName);

    std::vector<std::string> *splitFile();
};

#endif // FLIGHT_PROJECT_LEXERFILE_H
