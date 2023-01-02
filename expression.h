#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<bits/stdc++.h>
using namespace std;

class Expression{
    public:
        Expression(string _expression=""):expression(_expression){};
        Expression(Expression &p);
        virtual ~Expression(){};

        void change();//将expression分段,放入str_expression中
        
        string expression;
        vector<string>str_expression;
};

#endif//EXPRESSION_H
