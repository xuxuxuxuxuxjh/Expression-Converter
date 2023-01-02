#ifndef POSTFIX_H
#define POSTFIX_H

#include "expression.h"

class Postfix_Expression:public Expression{
    public:
        Postfix_Expression(string _expression="");
        Postfix_Expression(Postfix_Expression &p);
        ~Postfix_Expression(){};

        void Infix_to_Postfix(vector<string>str);
        void Prefix_to_Postfix(vector<string>str);

        double calculation();
};

#endif//POSTFIX_H
