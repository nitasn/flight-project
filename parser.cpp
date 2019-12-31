#include "parser.h"
#include "Expression.h"
#include "lexer.h"
#include "singltonGlobals.h"

double evaluateExpression(string& exp_str)
{
    lexer lexerSplit;
    lexerSplit.splitTheLine(exp_str);
    vector<string>* exp_tokens = lexerSplit.getVectorLexer();
    Interpreter interpreter;

    VarsMap::do_synchronously([&]() { // מפעיל ומבטל את הלוק של המפה בעצמו

        map<string, Var *> * vars = VarsMap::mapSingleton.it;

        for (string& token : *exp_tokens)
            if (vars->find(token) != vars->end())
                interpreter.upDateMapValue(token, vars->at(token)->data);

    });

    Expression *expression = nullptr;
    try { expression = interpreter.interpret(exp_str); }
    catch (...) {
        delete expression;
        delete exp_tokens;
        throw AssigningInvalidExpression();
    }
    double result = expression->calculate();
    delete expression;
    delete exp_tokens;
    return result;
}

// אפשר לקרוא לה גם מתוך פקודת איף וגם מתוך ה-מיין עבור כל הקוד...
void parse(vector<string>::iterator iter, vector<string>::iterator end)
{
    cout << "here yay" << endl;

    Command* cmd;

    while (iter != end)
    {
        if (CommandFactory::IsCommand(*iter))  // אם זו פקודה
        {
            cmd = CommandFactory::GetCmdObject(*iter); // הנה אובייקט של הפקודה
        }
        else // זה כנראה משתנה
        {
            cmd = new updateVarCommand(); // אז הנה אובייקט של פקודה שמעדכנת ערך של משתנה
        }
        iter = cmd->execute(iter + 1); // מריצים את הפקודה, היא מחזירה את מיקומו החדש של האיטר

        delete cmd;
    }
}