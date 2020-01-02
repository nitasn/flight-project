//
// Created by Nitsan BenHanoch on 01/01/2020.
//

#ifndef FLIGHT_PROJECT_EXPRESSIONINTERPRETER_H
#define FLIGHT_PROJECT_EXPRESSIONINTERPRETER_H


#include <iostream>
#include "Expression.h"
#include "globals_singleton.h"
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <utility>
#include <cmath>

using namespace std;

/**
 * Expression Interface
 */
class Expression
{

public:
    virtual double calculate() = 0;

    virtual ~Expression() = default;
};


class Value : public Expression
{
    const double value;

public:
    explicit Value(double val) : value(val)
    {}

    double calculate() override
    { return value; }
};

struct Variable : public Expression
{
    double value;

    const string name;

    Variable(string nam, double val) : name(std::move(nam)), value(val)
    {}

    explicit Variable(string nam) : name(std::move(nam))
    { value = NAN; }

    double calculate() override
    { return value; }
};


class BinaryOperator : public Expression
{

public:
    ~BinaryOperator() override
    {
        delete left;
        delete right;
    }

protected:
    Expression *left{}, *right{};
};

class UnaryOperator : public Expression
{

public:
    ~UnaryOperator() override
    {
        delete expression;
    }

protected:
    Expression *expression;
};

class Plus : public BinaryOperator
{

public:
    Plus(Expression *lef, Expression *rig)
    {
        this->left = lef;
        this->right = rig;
    }

    double calculate() override;
};

class Minus : public BinaryOperator
{

public:
    Minus(Expression *lef, Expression *rig)
    {
        this->left = lef;
        this->right = rig;
    }

    double calculate() override;
};

class Mul : public BinaryOperator
{

public:
    Mul(Expression *lef, Expression *rig)
    {
        this->left = lef;
        this->right = rig;
    }

    double calculate() override;
};

class Div : public BinaryOperator
{

public:
    Div(Expression *lef, Expression *rig)
    {
        this->left = lef;
        this->right = rig;
    }

    class DivisionByZero : exception
    {
    };

    double calculate() override;
};

class UPlus : public UnaryOperator
{

public:
    explicit UPlus(Expression *exp)
    {
        this->expression = exp;
    }

    double calculate() override;
};

class UMinus : public UnaryOperator
{

public:
    UMinus(Expression *exp)
    {
        this->expression = exp;
    }

    double calculate() override;
};


//*** interpreter goes here

/**
 * holds the expression itself, and a vector of pointers to all the inner variables,
 * so we can easily plug new values to the expression's variables
 */
struct ExpressionWrapper
{
    Expression *expression;
    vector<Variable *> *pToVars;

    ~ExpressionWrapper()
    {
        delete pToVars;
        delete expression;
    }

    /**
     * does apply VarsMap::do_synchronously
     */
    void update_values()
    {
        app::globals->do_with_vars_map([&]() // מפעיל את הלוק של המפה, מריץ את הבלוק, ועושה אנלוק למפה
        {
            map<string, Var *> *vars = app::globals->varsMap;

            for (Variable *exp_var : *this->pToVars) {
                if (vars->find(exp_var->name) != vars->end()) {
                    exp_var->value = vars->at(exp_var->name)->data;
                }
            }
        });
    }
};

class Interpreter
{
    static string clear_whitespaces(const string &str);

    static queue<string> *from_infix_string(const string &str);

    static ExpressionWrapper *from_postfix_strings_queue(queue<string> *queue);

public:
    static ExpressionWrapper *interpret(const string &str);
};


#endif //FLIGHT_PROJECT_EXPRESSIONINTERPRETER_H
