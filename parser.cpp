#include "parser.h"
#include "globals_singleton.h"


using namespace std;


/// must be called when varsMap's mutex is unlocked
double evaluateExpressionStr(string& exp_str)
{
    auto exp = Interpreter::interpret(exp_str);

    exp->update_values(); // מציב את ערכם הנוכחי של המשתנים באקספרשן מתוך מפת המשתנים הגלובלית

    double result = exp->expression->calculate();
    delete exp;

    return result;
}

void parse(vector<string>::iterator iter, vector<string>::iterator end)
{
    Command* cmd;

    while (iter != end)
    {
        if (app::globals->verbose)
        {
            cout << "parser is at the token: " << *iter << endl;
        }

        if (CommandFactory::IsCommand(*iter))  // אם זו פקודה
        {
            cmd = CommandFactory::GetCmdObject(*iter++); // מקדמים את האיטר לארגומנטים של הפקודה
        }
        else // זה כנראה משתנה
        {
            if (app::globals->varsMap->find(*iter) == app::globals->varsMap->end())
            {
                throw UnknownCommand(); // אם זה לא משתנה - אז מה זה בדיוק
            }

            cmd = new updateVarCommand(); // פקןדה מיוחדת. הארגומנט שלה הוא השם של המשתנה - כלומר איפה שהאיטר עכשיו
        }
        iter = cmd->execute(iter); // מריצים את הפקודה, היא מחזירה את מיקומו החדש של האיטר

        delete cmd;
    }
}