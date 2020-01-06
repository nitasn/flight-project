//
// Created by Nitsan BenHanoch on 01/01/2020.
//

#include "ExpressionInterpreter.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <sstream>

double Plus::calculate() { return left->calculate() + right->calculate(); }

double Minus::calculate() { return left->calculate() - right->calculate(); }

double Mul::calculate() { return left->calculate() * right->calculate(); }

double Div::calculate()
{
    double temp = right->calculate();

    if (temp == 0) throw DivisionByZero();

    return left->calculate() / temp;
}

double UPlus::calculate() { return +expression->calculate();}

double UMinus::calculate() { return -expression->calculate(); }




//** interpreter goes here


using namespace std;



bool is_number(const string &s)
{
    try {
        std::stod(s);
        return true;
    }
    catch (...) {
        return false;
    }
}

void print(stack<char> s) {
    cout << "stack contains: ";
    while (!s.empty()) {
        char c = s.top();
        cout << c;
        s.pop();
        if (!s.empty())
            cout << ", ";
    }
    cout << endl;
}

void print(queue<string> s) {
    cout << "queue contains: ";
    while (!s.empty()) {
        string c = s.front();
        cout << c;
        s.pop();
        if (!s.empty())
            cout << ", ";
    }
    cout << endl;
}

ExpressionWrapper *Interpreter::interpret(const string &str)
{
    string clean_str = clear_whitespaces(str); // no whitespaces...

    queue<string> *postfix_queue = from_infix_string(clean_str);

    ExpressionWrapper *result = from_postfix_strings_queue(postfix_queue);

    delete postfix_queue;

    return result;
}

queue<string> *Interpreter::from_infix_string(const string &str)
{
    stack<char> stack; // helper stack: contains only operands, and therefore the type is chars

    auto *queue = new ::queue<string>(); // result queue (thus stored in heap)
    // contains (potentially multi-letter) variable names and str repr of fractions, therefore its of strings

    auto to_string = [](char c) { return string(1, c); };

    auto pop_to_queue_while_top_is = [&](const set<char> &set) {
        while (!stack.empty() && set.find(stack.top()) != set.end()) // while top exists and is present in the set
        {
            queue->push(to_string(stack.top()));
            stack.pop();
        }
    };

    auto is_operator_char = [](char c) {
        // of course one could make a decision tree, or create a hash table in advance, but let's not get too crazy
        return c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')';
    };

    auto is_unary_operator_at = [&str](size_t i) {
        return (str[i] == '+' || str[i] == '-') && (i == 0
                                                    || str[i - 1] == '(' || str[i - 1] == '*' || str[i - 1] == '/'
                                                    || str[i - 1] == '+' || str[i - 1] == '-');
    };

    for (size_t i = 0; i < str.length(); i++) {
        if (is_unary_operator_at(i)) {
            pop_to_queue_while_top_is({'@', '#'}); // '@' and '#' represent the unary operators UMinus and UPlus
            stack.push(str[i] == '-' ? '@' : '#'); // respectively, to distinguish between them and regular +, -
        } else if (str[i] == '*' || str[i] == '/') {
            pop_to_queue_while_top_is({'*', '/', '@', '#'}); // all operators of precedence that is less than
            stack.push(str[i]);                                  // or equal to ours
        } else if (str[i] == '+' || str[i] == '-') {
            pop_to_queue_while_top_is({'*', '/', '+', '-', '@', '#'});
            stack.push(str[i]);
        } else if (str[i] == '(') {
            stack.push('(');
        } else if (str[i] == ')') {
            pop_to_queue_while_top_is({'*', '/', '+', '-', '@', '#'});

            if (stack.empty() || stack.top() != '(')
                throw "mismatched parentheses: too many ')'";

            stack.pop(); // get rid of the matching '('
        } else // we must have found a name of a variable or a literal number (something like "a123" or 3.14")
        {
            stringstream token;
            do {
                token << str[i++];
            } while (i < str.length() && !is_operator_char(str[i]));

            queue->push(token.str());

            i -= 1;
        }
    }
    while (!stack.empty()) // after going through all chars in str, pop anything left in queue to the stack
    {
        queue->push(to_string(stack.top()));

        if (stack.top() == '(')
            throw "mismatched parentheses: too many '('";

        stack.pop();
    }

    return queue; // postfix str-tokens queue
}

ExpressionWrapper *Interpreter::from_postfix_strings_queue(queue<string> *queue)
{
    stack<Expression *> stack;
    auto pToVars = new vector<ExpVar *>;

    auto pop_stack = [&stack]() {
        if (stack.empty())
            throw "illegal math expression: missing operands";
        auto expression = stack.top();
        stack.pop();
        return expression;
    };

    while (!queue->empty()) {
        string token = queue->front();
        queue->pop();

        if (token == "@")
        {
            stack.push(new UMinus(pop_stack()));
        }
        else if (token == "#")
        {
            stack.push(new UPlus(pop_stack()));
        }
        else if (token == "+")
        {
            auto right = pop_stack();
            auto left = pop_stack();
            stack.push(new Plus(left, right));
        }
        else if (token == "-")
        {
            auto right = pop_stack();
            auto left = pop_stack();
            stack.push(new Minus(left, right));
        }
        else if (token == "*")
        {
            auto right = pop_stack();
            auto left = pop_stack();
            stack.push(new Mul(left, right));
        }
        else if (token == "/")
        {
            auto right = pop_stack();
            auto left = pop_stack();
            stack.push(new Div(left, right));
        }
        else // if token is not an operator, then it's either a number or a variable
        {
            if (is_number(token)) // it's a number literal
            {
                double val = stod(token);
                auto valueObj = new Value(val);
                stack.push(valueObj);
            }
            else  // then it's a variable
            {
                auto *newVar = new ExpVar(token);
                stack.push(newVar);
                pToVars->push_back(newVar);
            }
        }
    }

    Expression *result = pop_stack();

    if (!stack.empty()) throw "illegal math expression: missing operators";

    return new ExpressionWrapper{result, pToVars};
}

string Interpreter::clear_whitespaces(const string &str)
{
    stringstream result;

    for (auto c : str)
    {
        if (!isspace(c))
        {
            result << c;
        }
    }
    return result.str();
}
