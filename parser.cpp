#include "parser.h"
#include "Expression.h"
#include "globals_singleton.h"

double evaluateExpressionStr(string& exp_str)
{
    auto exp = Interpreter::interpret(exp_str);
    exp->update_values();
    double result = exp->expression->calculate();
    delete exp;

    return result;
}

void parse(vector<string>::iterator iter, vector<string>::iterator end)
{
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