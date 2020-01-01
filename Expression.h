
#ifndef FLIGHT_PROJECT_EXPRESSION_H
#define FLIGHT_PROJECT_EXPRESSION_H

using namespace std;
#include "string"
#include <netdb.h>
#include <stack>
#include <map>
#include <queue>
#include <regex>

/**
 * Expression Interface
 */
class Expression {
public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

class BinaryOperatar: public Expression {
protected: Expression *leftExpression;
    Expression *rightExpression;
public: BinaryOperatar(Expression *leftExpression, Expression *rightExpression);
    ~BinaryOperatar();
};


class Plus: public BinaryOperatar {
protected: Expression *leftExpression;
    Expression *rightExpression;
public:Plus(Expression *leftExpression, Expression *rightExpression);
public: double calculate();
};


class Minus: public BinaryOperatar {
protected: Expression *leftExpression;
    Expression *rightExpression;
public:Minus(Expression *leftExpression, Expression *rightExpression);
public: double calculate();
};


class Mul: public BinaryOperatar {
protected: Expression *leftExpression;
    Expression *rightExpression;
public:Mul(Expression *leftExpression, Expression *rightExpression);
public: double calculate();
};


class Div: public BinaryOperatar {
protected: Expression *leftExpression;
    Expression *rightExpression;
public:Div(Expression *leftExpression, Expression *rightExpression);
public: double calculate();
};


class Value: public Expression {
protected: double value;
public:Value(double  value);
public: double calculate();
};


class UnaryOpertor: public Expression {
protected: Expression *thisExpression;
public: UnaryOpertor(Expression *thisExpression);
    ~UnaryOpertor();
};

class Variable: public Expression {
protected:
    string name;
    double value;
public: Variable(string name, double value);
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double);
    Variable& operator-=(double);
    Variable& operator--(int);
    Variable& operator++(int);
    double calculate();
};

class  Interpreter {
protected:
    string newExpression;
    queue<string> *numStack;
    map<string, int> opertorMap;
    map<string, Variable> *variableMap;
public: Interpreter();
    Expression *interpret(string thisExpression);
    void setVariables(string stringVariable);
    ~Interpreter();
    void checkOkFormt(string stringVariable);
    void upDateMapValue(string nameString, double valueString);
private: void createNumQueue();
    Expression *findTheAnser();
    void ifUnurySign(int i);
    bool pushUpParenthesis(stack<string> *opStack, int i);
    void adToMapOpertor();
    void creatExpression(stack<Expression*> *anserStack);
    void selectOpertorStack(stack<string> *opStack, string *stringToValue, int i);
    void puseOpertorStack(stack<string> *opStack, int i);
    void checkTheVariableHaveValue(string stringToValue);
    void checkOkParenthesisAndOpertor(string thisExpression);
};

#endif FLIGHT_PROJECT_EXPRESSION_H