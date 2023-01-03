#include "expression.h"

Expression::Expression(Expression &p)
{
    expression=p.expression;
}

bool Expression::check()//检查str_expression中的string是否合法
{
    for(string s:str_expression)
    {
        if(s.size()==1)continue;
        int sum=0;
        for(char ch:s)
        {
            if(ch=='.')sum++;
        }
        if(sum>1)return 0;
    }
    return 1;
}

void Expression::change()//将expression分段,放入str_expression中
{
    string number="";
    this->str_expression.clear();
    for(char ch:expression)
    {
        if(ch==' ')
        {
            if(number!="")str_expression.push_back(number);
            number="";
        }
        else{
            number+=ch;
        }
    }
    if(number!="")str_expression.push_back(number);
    if(!check())throw "error";
}
