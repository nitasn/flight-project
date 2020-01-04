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
    app::globals = new app;

    app::globals->verbose = false; // אם זה טרו, הקוד מוסיף כל מיני הדפסות כדי לספר לנו על דברים שקורים ברקע

    string code_filename = "/Users/nitsan/Downloads/flight_simulator/fly.txt";

    vector<string> *tokens = nullptr;

    try
    {
        lexerFile lex(code_filename);
        tokens = lex.splitFile();

//        for (auto &token : *tokens)
//            cout << token << endl;

        parse(tokens->begin(), tokens->end());
    }
    catch (char const* e)
    {
        cerr << e << endl;
    }


    delete tokens;
    delete app::globals;
}