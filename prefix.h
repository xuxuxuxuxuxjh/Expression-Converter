#ifndef PREFIX_H
#define PREFIX_H

#include "expression.h"

class Prefix_Expression:public Expression{
    public:
        Prefix_Expression(string _expression="");
        Prefix_Expression(Prefix_Expression &p);
        ~Prefix_Expression(){};

        void Infix_to_Prefix(vector<string>str);
        void Postfix_to_Prefix(vector<string>str);
};

#endif//PREFIX_H
