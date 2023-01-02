#ifndef INFIX_H
#define INFIX_H

#include "expression.h"

class Infix_Expression:public Expression{
    public:
        Infix_Expression(string _expression="");
        Infix_Expression(Infix_Expression &p);
        ~Infix_Expression(){};

        void Postfix_to_Infix(vector<string>str);
        void Prefix_to_Infix(vector<string>str);
};

#endif//INFIX_H
