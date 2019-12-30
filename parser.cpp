#include "parser.h"
#include "Expression.h"
#include "lexer.h"
#include "singltonGlobals.h"

// אפשר לקרוא לה גם מתוך פקודת איף וגם מתוך ה-מיין עבור כל הקוד...
void parse(vector<string>::iterator iter, vector<string>::iterator end)
{
    while (iter != end){
        Command* cmd;

        if (CommandFactory::IsCommand(*iter)){ // אם זו פקודה
            cmd = CommandFactory::GetCmdObject(*iter); // הנה אובייקט של הפקודה
        }else{
            cmd = new updateVarCommand(*iter); // זה כנראה משתנה
        }
        iter = cmd->execute(iter + 1); // מריצים את הפקודה, היא מחזירה את מיקומו החדש של האיטר
        delete cmd;
    }
}

double evaluateExpression(string& exp_str)
{
    lexer lexerSplit;
    lexerSplit.splitTheLine(exp_str);
    vector<string>* exp_tokens = lexerSplit.getVectorLexer();
    Interpreter interpreter;
    VarsMap::mutexSingleton.it->lock();
    map<string, Var *> * vars = VarsMap::mapSingleton.it;
    for (string& token : *exp_tokens)
        if (vars->find(token) != vars->end())
            interpreter.upDateMapValue(token, vars->at(token)->data);
    VarsMap::mutexSingleton.it->unlock();
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