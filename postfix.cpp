#include "postfix.h"
#include "infix.h"
#include "function.h"

Postfix_Expression::Postfix_Expression(Postfix_Expression &p)
{
    expression=p.expression;
}

Postfix_Expression::Postfix_Expression(string _expression)
{
    expression=_expression;
}

void Postfix_Expression::Infix_to_Postfix(vector<string>str)
{
    stack<string>sta;
    vector<string>res;
    for(string s:str)
    {
        if(s[0]>='0'&&s[0]<='9')res.push_back(s);
        if(s=="(")sta.push(s);
        if(s=="+"||s=="-")
        {
            while(!sta.empty()&&sta.top()!="(")
            {
                res.push_back(sta.top());
                sta.pop();
            }
            sta.push(s);
        }
        if(s=="*"||s=="/")
        {
            while(!sta.empty()&&(sta.top()=="*"||sta.top()=="/"||sta.top()=="^"))
            {
                res.push_back(sta.top());
                sta.pop();
            }
            sta.push(s);
        }
        if(s=="^")
        {
            while(!sta.empty()&&sta.top()=="^")
            {
                res.push_back(sta.top());
                sta.pop();
            }
            sta.push(s);
        }
        if(s==")")
        {
            while(sta.top()!="(")
            {
                res.push_back(sta.top());
                sta.pop();
            }
            sta.pop();
        }
    }
    while(!sta.empty())
    {
        res.push_back(sta.top());
        sta.pop();
    }
    expression="";
    for(string s:res)
    {
        expression+=s+" ";
    }
    change();
}

void Postfix_Expression::Prefix_to_Postfix(vector<string>str)
{
    //前缀转中缀
    Infix_Expression infix;
    infix.Prefix_to_Infix(str);
    infix.change();

    //中缀转后缀
    Infix_to_Postfix(infix.str_expression);
    change();
}

double Postfix_Expression::calculation()
{
    vector<double>res;
    change();
    for(string s:str_expression)
    {
        if(s[0]>='0'&&s[0]<='9')
        {
            res.push_back(str_to_double(s));
        }
        if(s=="+")
        {
            int n=res.size()-1;
            res[n-1]+=res[n];
            res.pop_back();
        }
        if(s=="-")
        {
            int n=res.size()-1;
            res[n-1]-=res[n];
            res.pop_back();
        }
        if(s=="*")
        {
            int n=res.size()-1;
            res[n-1]*=res[n];
            res.pop_back();
        }
        if(s=="/")
        {
            int n=res.size()-1;
            res[n-1]/=res[n];
            res.pop_back();
        }
        if(s=="^")
        {
            int n=res.size()-1;
            res[n-1]=kuai(res[n-1],res[n]);
            res.pop_back();
        }
    }
    return res[0];
}
