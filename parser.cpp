#include "parser.h"
#include "Expression.h"
#include "lexer.h"

// אפשר לקרוא לה גם מתוך פקודת איף וגם מתוך ה-מיין עבור כל הקוד...
void parse(vector<string>::iterator iter, vector<string>::iterator end)
{
    while (iter != end)
    {
        if (CommandFactory::IsCommand(*iter)) // אם זו פקודה
        {
            Command* cmd = CommandFactory::GetCmdObject(*iter); // הנה אובייקט של הפקודה
            iter = cmd->execute(iter + 1); // מריצים את הפקודה, היא מחזירה את מיקומו החדש של האיטר
            delete cmd;
        }
        else
        {
            // אז זה השמה למשתנה, ...
        }
    }
}

double evaluateExpression(string& exp_str)
{
    splitTheLine(exp_str);
    vector<string>* exp_tokens = returnVectorLexer();
    Interpreter interpreter;

    for (string token : *exp_tokens)
        if (isInMap(token, vars))
            interpreter.setVariables(var(token, vars[token]->data);

    Expression *expression = nullptr;

    try { expression = interpreter.interpret(exp_str); }
    catch (...) {
        delete expression;
        delete exp_tokens;
        throw VarAssigningNotLegal();
    }

    double result = expression->calculate();
    delete expression;
    delete exp_tokens;

    return result;
}