#include "expression.h"

Expression::Expression(Expression &p)
{
    expression=p.expression;
}

void Expression::change()
{
    string number="";
    str_expression.clear();
    for(char ch:expression)
    {
        if((ch>='0'&&ch<='9')||ch=='.')number=number+ch;
        else{
            if(number!="")str_expression.push_back(number);
            number="";
            string s="";
            s+=ch;
            if(ch!=' ')str_expression.push_back(s);
        }
    }
    if(number!="")str_expression.push_back(number);
}
