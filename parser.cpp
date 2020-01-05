#include "parser.h"
#include "globals_singleton.h"


using namespace std;



/**
 * evaluateExpressionStr calculate expression that in string to num
 * @param exp_str string expression
 * @return value expression
 */
double evaluateExpressionStr(string& exp_str)
{
    /// must be called when varsMap's mutex is unlocked
    auto exp = Interpreter::interpret(exp_str);

    exp->update_values(); //update var that in expression according map

    double result = exp->expression->calculate();
    delete exp;

    return result;
}
/**
 * parse while the vector command not ending, execute the commands.
 * create command with argument, or update var
 * @param iter to begin block in vector
 * @param end iter to end block
 */
void parse(vector<string>::iterator iter, vector<string>::iterator end)
{
    Command* cmd;

    while (iter != end) // while not end of block
    {
        if (app::globals->verbose)
        {
            cout << "parser is at the token: " << *iter << endl;
        }

        if (CommandFactory::IsCommand(*iter))  // if this command
        {
            cmd = CommandFactory::GetCmdObject(*iter++); // create command object with the input class
        }
        else // this is var update
        {
            if (app::globals->varsMap->find(*iter) == app::globals->varsMap->end())
            {
                throw UnknownCommand(); // error - this is not command and not var
            }

            cmd = new updateVarCommand(); // update var. not need argument becuse the command is the argument
        }
        iter = cmd->execute(iter); //execute the command, that return updating itar

        delete cmd;
    }
}