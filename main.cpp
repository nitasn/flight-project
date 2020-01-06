//
// Created by Nitsan BenHanoch on 15/12/2019.
//


#include "globals_singleton.h"
#include "lexerFile.h"
#include "parser.h"


using namespace std;


app *app::globals;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "usage: " << argv[0] << " [CODE FILE TO INTERPRET]" << endl;
        return -1;
    }

    app::globals = new app;

    app::globals->verbose = false; // אם זה טרו, הקוד מוסיף כל מיני הדפסות כדי לספר לנו על דברים שקורים ברקע

    string code_filename = argv[1];

    vector<string> *tokens = nullptr;

    try
    {
        lexerFile lex(code_filename);
        tokens = lex.splitFile();

        if (app::globals->verbose)
        {
            cout << "<lexer output>" << endl;

            for (auto &token : *tokens)
                cout << token << endl;

            cout << "</lexer output>" << endl << endl;
        }

        parse(tokens->begin(), tokens->end());
    }
    catch (char const* e)
    {
        cerr << e << endl;
    }


    delete tokens;
    delete app::globals;
}