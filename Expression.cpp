//
// Created by hodyah on 25/12/2019.
//

#include "Expression.h"
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <regex>
#include <iostream>

/**.
 * BinaryOperatar cunstractor
 * ubstract class
 * @param leftExpression
 * @param rightExpression
 */
BinaryOperatar:: BinaryOperatar(Expression *leftExpression1, Expression *rightExpression1):
        Expression() {
    this->leftExpression = leftExpression1;
    this->rightExpression = rightExpression1;
}
/**.
 * BinaryOperatar distractor
 */
BinaryOperatar::~BinaryOperatar() {
    delete(this->leftExpression);
    delete(this->rightExpression);
}
/**.
 * Plus cunstractor
 * @param leftExpression
 * @param rightExpression
 */
Plus:: Plus(Expression *leftExpression1, Expression *rightExpression1):
        BinaryOperatar(leftExpression1, rightExpression1) {
    this->leftExpression = leftExpression1;
    this->rightExpression = rightExpression1;
}
/**.
 * do plus for the expression
 * @return value of plus
 */
double Plus::calculate() {
    return (this->leftExpression->calculate() + this->rightExpression->calculate());
}
/**.
 * Minus constuctor
 * @param leftExpression
 * @param rightExpression
 */
Minus:: Minus(Expression *leftExpression1, Expression *rightExpression1):
        BinaryOperatar(leftExpression1, rightExpression1) {
    this->leftExpression = leftExpression1;
    this->rightExpression = rightExpression1;
}
/**.
 * do minus for the expression
 * @return value of minus
 */
double Minus::calculate() {
    return (this->leftExpression->calculate() - this->rightExpression->calculate());
}
/**.
 * Mul constructor
 * @param leftExpression
 * @param rightExpression
 */
Mul:: Mul(Expression *leftExpression1, Expression *rightExpression1):
        BinaryOperatar(leftExpression1, rightExpression1) {
    this->leftExpression = leftExpression1;
    this->rightExpression = rightExpression1;
}
/**.
 * do mul for the expression
 * @return value of mul
 */
double Mul::calculate() {
    return (this->leftExpression->calculate() * this->rightExpression->calculate());
}
/**.
 * Div constructor
 * @param leftExpression
 * @param rightExpression
 */
Div:: Div(Expression *leftExpression1, Expression *rightExpression1):
        BinaryOperatar(leftExpression1, rightExpression1) {
    this->leftExpression = leftExpression1;
    this->rightExpression = rightExpression1;
}
/**.
 * do div for the expression
 * trhow error if you div of 0
 * @return value of div
 */
double Div::calculate() {
    if(this->rightExpression->calculate() == 0){
        throw "error: cannot divide on zero.";
    }
    return (this->leftExpression->calculate() / this->rightExpression->calculate());
}
/**.
 * Value costructor
 * @param value
 */
Value:: Value(double value1) {
    this->value = value1;
}
/**.
 * do Value
 * @return double of value
 */
double Value:: calculate() {
    return this->value;
}
/**.
 * UnaryOpertor constructor.
 * ubstract class
 * @param thisExpression
 */
UnaryOpertor::UnaryOpertor(Expression *thisExpression1):
        Expression()  {
    this->thisExpression = thisExpression1;
}
/**.
 * UnaryOpertor distructor
 */
UnaryOpertor::~UnaryOpertor() {
    delete(this->thisExpression);
}
/**.
 * Variable constructor
 * @param name
 * @param value
 */
Variable::Variable(string name1, double value1) {
    this->name = name1;
    this->value = value1;
}
/**.
 * do Variable
 * @return this value of variable
 */
double Variable:: calculate() {
    return this->value;
}
/**.
 * operator++ do this value ++
 * @return pointar to this
 */
Variable& Variable:: operator++ (){
    ++this->value;
    return *this;
}
/**.
 * operator-- do this value --
 * @return pointar to this
 */
Variable& Variable:: operator-- (){
    --this->value;
    return *this;
}
/**.
 * operator-- to  do this --value
 * @return pointar to this
 */
Variable& Variable:: operator-- (int){
    this->value--;
    return *this;
}
/**.
 * operator++ to  do this ++value
 * @return pointar to this
 */
Variable& Variable:: operator++ (int){
    this->value++;
    return *this;
}
/**.
 * operator+= to  do this value + x
 * @param x add to this value
 * @return this
 */
Variable& Variable:: operator+= (double x){
    this->value = (this->value + x);
    return *this;
}
/**.
 * operator-= to  do this value - x
 * @param x minus to this value
 * @return this
 */
Variable& Variable:: operator-= (double x){
    this->value = (this->value - x);
    return *this;
}
/**.
 * Interpreter constructor
 * create map variable and stack to num
 */
Interpreter:: Interpreter(){
    this->numStack = new queue<string>();
    this->variableMap = new map<string, Variable>;
}
/**.
 * Interpreter discructor
 */
Interpreter::~Interpreter(){
    delete (this->numStack);
    map<string, Variable>::iterator lopOnMap;
    for (lopOnMap = this->variableMap->begin(); lopOnMap!=this->variableMap->end(); lopOnMap++){
        this->variableMap->erase(lopOnMap);
    }
    delete (this->variableMap);

}
/**.
 * interpret return Expression according the string
 * @param thisExpression the expression in string
 * @return Expresssion
 */
Expression* Interpreter::interpret(string thisExpression) {
    checkOkParenthesisAndOpertor(thisExpression);
    this->newExpression = thisExpression;
    this->createNumQueue();
    return this->findTheAnser();
}
/**.
 * createNumQueue create queue with num and opretor from the string
 * according priorities
 */
void Interpreter:: createNumQueue() {
    stack<string> *opStack = new stack<string>();
    string stringToValue;
    adToMapOpertor();
    try{
        for (unsigned int i = 0; i < this->newExpression.length(); i++) {
            string s = "";
            if (isdigit(this->newExpression[i]) || isalpha(this->newExpression[i]) || this->newExpression[i] == '_') {
                stringToValue = stringToValue + newExpression[i];
            } else {
                if (this->newExpression[i] == '.') {
                    stringToValue = stringToValue + newExpression[i];
                }else{
                    if(isalpha(stringToValue[0])){
                        checkTheVariableHaveValue(stringToValue);
                    }
                    selectOpertorStack(opStack, &stringToValue, i);
                }
            }
        }
        if (!stringToValue.empty()) {
            numStack->push(stringToValue);
        }
        while (!opStack->empty()) {
            numStack->push(opStack->top());
            opStack->pop();
        }
        delete(opStack);
    } catch(exception e) {
        throw ("bad input");
    }
}
/**.
 * pup num and opretor from queue and create new expression according the queue
 * @return new Expression
 */
Expression *Interpreter::findTheAnser() {
    stack<Expression *> *anserStack = new stack<Expression *>;
    double stringToValue = 0;
    while (!this->numStack->empty()) {
        // this is number
        if (isdigit(this->numStack->front()[0])) {
            stringToValue = atof((this->numStack->front().c_str()));
            anserStack->push((new Value(stringToValue)));
            this->numStack->pop();
        } else {
            if (isalpha(this->numStack->front()[0]) || this->numStack->front()[0] == '_') {
                Variable *a = new Variable(this->numStack->front(), (this->variableMap->at(
                        this->numStack->front())).calculate());
                anserStack->push(a);
                this->numStack->pop();
            } else {
                creatExpression(anserStack);
            }
        }
    }
    Expression *anser = (anserStack->top());
    delete (anserStack);
    return anser;
}
/**.
 * add variable for the expression to map
 * @param stringVariable the variables.
 */
void Interpreter::setVariables(string stringVariable) {
    checkOkFormt(stringVariable);
    string nameString;
    double valueString = 0;
    for (unsigned int i = 0; i < stringVariable.size(); i++) {
        while (stringVariable[i] != '=') {
            nameString = nameString + stringVariable[i];
            ++i;
        }
        i++;
        string s;
        while (stringVariable[i] != ';' && i < stringVariable.size()) {
            s += stringVariable[i];
            i++;
        }
        valueString = atof(s.c_str());
        upDateMapValue(nameString, valueString);
        nameString.clear();
    }
}
/**.
 * ceack if this opretor is unaury opretor
 * @param i the currant opretor in string
 */
void Interpreter::ifUnurySign(int i) {
    string s;
    if ( i == 0 || ((this->opertorMap.at(s += newExpression[i]) == 2) && (newExpression[i - 1] == '('))) {
        numStack->push("0");
    }
}
 /** check if this variable in map, chnge her value if yes and add to map if no
 /* @param nameString name of the variable
 /* @param valueString value of the variable
 */
void Interpreter::upDateMapValue(string nameString, double valueString) {
    if (this->variableMap->find(nameString) != this->variableMap->end()) {
        // todo is there a memory leak - cause we are not deleting the old var!
        this->variableMap->erase(nameString);
    }
    (this->variableMap)->emplace(nameString, *(new Variable(nameString, valueString)));
}
/**.
 * pushUpParenthesis check priorities of the current opretor in queqe and the
 * new opretor that need to add
 * @param opStack stack of oprator
 * @param i current place in string
 * @return true if puse him, false else
 */
bool Interpreter::pushUpParenthesis(stack<string> *opStack, int i) {
    if (newExpression[i] == ')') {
        while (!opStack->empty() && (opStack->top() != "(")) {
            numStack->push(opStack->top());
            opStack->pop();
        }
        if (!opStack->empty()) {
            opStack->pop();
        }
        for (int j = 0; j < i-1  ; j++){
            if (newExpression[i - j] == '-' || newExpression[i - j] == '+' || newExpression[i - j] == '*' ||
                newExpression[i - j] == '/'){
                break;
            }
            if ((newExpression[i - j]) == '(' && ((newExpression[i - j -1] == '+') ||
                                                  ((newExpression[i - j -1] == '-')))) {
                numStack->push(opStack->top());
                opStack->pop();
            }
        }
        return true;
    }
    return false;
}
/**.
 * ad variable to opretor map according priorities in map
 */
void Interpreter::adToMapOpertor() {
    string t = "";
    this->opertorMap[t += '('] = 4;
    t.clear();
    this->opertorMap[t += ')'] = 1;
    t.clear();
    this->opertorMap[t += '+'] = 2;
    t.clear();
    this->opertorMap[t += '-'] = 2;
    t.clear();
    this->opertorMap[t += '*'] = 3;
    t.clear();
    this->opertorMap[t += '/'] = 3;
}
/**.
 * creat the new expression accorsing the opretor
 * @param anserStack stack with the expression that crete from the queqe
 */
void Interpreter::creatExpression(stack<Expression*> *anserStack) {
    Expression *rightExpression = ((anserStack->top()));
    anserStack->pop();
    Expression *leftExpression = (anserStack->top());
    anserStack->pop();
    if (this->numStack->front()[0] == '+') {
        anserStack->push((new Plus(leftExpression, rightExpression)));
    } else if (this->numStack->front()[0] == '-') {
        anserStack->push(new Minus(leftExpression, rightExpression));
    } else if (this->numStack->front()[0] == '/') {
        anserStack->push((new Div(leftExpression, rightExpression)));
    } else {
        anserStack->push((new Mul(leftExpression, rightExpression)));
    }
    this->numStack->pop();
}
/**
 * select the opretor stack according priorities
 * @param opStack stack from opretor
 * @param stringToValue the string of num
 * @param i the current place in the string expression
 */
void Interpreter::selectOpertorStack(stack<string> *opStack, string *stringToValue, int i) {
    string s;
    if (!(stringToValue->empty())) {
        numStack->push(*stringToValue);
        stringToValue->clear();
    }
    if (!opStack->empty()) {
        if (opertorMap[s += newExpression[i]] >= opertorMap[opStack->top()] ||
            opStack->top() == "(") {
            puseOpertorStack(opStack, i);
        } else {
            pushUpParenthesis(opStack, i);
        }
    } else {
        s.clear();
        ifUnurySign(i);
        opStack->push(s += newExpression[i]);
    }
}
/**.
 * puse Opertor Stack if () end
 * @param opStack stack opretor
 * @param i current value in string expression
 */
void Interpreter::puseOpertorStack(stack<string> *opStack, int i) {
    string s;
    if (opertorMap.at(s += newExpression[i]) == opertorMap.at(opStack->top()) &&
        newExpression[i] != '(') {
        numStack->push(opStack->top());
        opStack->pop();
    }
    s.clear();
    ifUnurySign(i);

    if (!pushUpParenthesis(opStack, i)) {
        opStack->push(s += newExpression[i]);
    }
}
/**.
 * check that the formt of variable name good
 * @param stringVariable the variable string
 */
void Interpreter::checkOkFormt(string stringVariable){
    smatch formtVariables;
    stack<string> *stringStack = new stack<string>;
    string addString;
    for (unsigned int i = 0; i < stringVariable.size(); i++){
        if (stringVariable[i] == ';' || stringVariable[i] == '='){
            stringStack->push(addString);
            addString.clear();
            continue;
        }
        addString = addString + stringVariable[i];
    }
    stringStack->push(addString);
    regex b = regex("^([ ]?[-]?[+]?[0-9]+(.[0-9]+)?)$");
    regex a = regex("^([_a-zA-Z]+[a-zA-z0-9_]*[ ]?)$");
    while (!stringStack->empty()){
        bool anser2 = regex_match(stringStack->top(), formtVariables , b);
        stringStack->pop();
        bool anser1 = regex_match(stringStack->top(), formtVariables , a);
        stringStack->pop();
        if(!anser1 || !anser2){
            throw ("bad input");
        }
    }
}
/**.
 *check that the expression leggle with him Parenthesis and opretor
 * @param thisExpression string of expression
 */
void Interpreter::checkOkParenthesisAndOpertor(string thisExpression) {
    stack<char> *parenthesisStack = new stack<char>();
    bool IamOpertor = false;
    for (unsigned int i = 0; i < thisExpression.size(); i++){
        if((thisExpression[i] == ')') || (thisExpression[i] == '(')) {
            if(!parenthesisStack->empty() && (thisExpression[i] == ')') && (parenthesisStack->top() == '(')){
                parenthesisStack->pop();
            } else {
                parenthesisStack->push(thisExpression[i]);
            }
            if((thisExpression[i] == ')') && (i + 1) < thisExpression.size()) {
                if ((thisExpression[i + 1] != '/') && (thisExpression[i + 1] != '+') &&
                    (thisExpression[i + 1] != '*') && (thisExpression[i + 1] != '-') &&
                    (thisExpression[i + 1] != ')')) {
                    throw ("bad input");
                }
            }
        } else if(thisExpression[i] == '/'|| thisExpression[i] == '+' || thisExpression[i] == '*' || thisExpression[i] == '-'){
            if (IamOpertor){
                throw ("bad input");
            }
            IamOpertor = true;
            continue;
        }
        IamOpertor = false;
    }
    if (!parenthesisStack->empty()){
        throw ("bad input");
    }
    delete(parenthesisStack);
}
/**.
 *check that the variable name have value in the map
 * @param stringToValue string of variable name
 */
void Interpreter::checkTheVariableHaveValue(string stringToValue){
    if (this->variableMap->count(stringToValue) > 0){
        return;
    }
    throw 1;
}
