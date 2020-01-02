//
// Created by Nitsan BenHanoch on 15/12/2019.
//


#include "globals_singleton.h"
#include "lexerFile.h"
#include "parser.h"

app *app::globals;

int main(int argc, char *argv[])
{
    app::globals = new app;

    string code_filename = "~/CLionProjects/flight-project/fly.txt";

    vector<string> *tokens = nullptr;

    try
    {
        lexerFile lex(code_filename);
        tokens = lex.splitFile();
        parse(tokens->begin(), tokens->end());
    }
    catch (char const* e)
    {
        cout << e << endl;
    }

    delete tokens;
    delete app::globals;
}