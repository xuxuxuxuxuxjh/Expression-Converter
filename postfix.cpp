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
        if((s[0]>='0'&&s[0]<='9')||s.size()>1)res.push_back(s);
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
            while(!sta.empty()&&sta.top()!="(")
            {
                res.push_back(sta.top());
                sta.pop();
            }
            if(!sta.empty())sta.pop();
            else throw "error";//括号不匹配
        }
    }
    while(!sta.empty())
    {
        res.push_back(sta.top());
        sta.pop();
    }
    this->expression="";
    for(string s:res)
    {
        this->expression+=s+" ";
    }
    try{
        this->change();
    }catch(...){
        throw "error";
    }
}

void Postfix_Expression::Prefix_to_Postfix(vector<string>str)
{
    try{
        //前缀转中缀
        Infix_Expression infix;
        infix.Prefix_to_Infix(str);
        infix.change();

        //中缀转后缀
        Infix_to_Postfix(infix.str_expression);
        this->change();
    }catch(...){
        throw "error";
    }
}

double Postfix_Expression::calculation()
{
    vector<double>res;
    this->change();
    for(string s:str_expression)
    {
        if((s[0]>='0'&&s[0]<='9')||s.size()>1)
        {
            res.push_back(str_to_double(s));
        }
        if(s=="+")
        {
            int n=res.size()-1;
            if(n<=0)throw "error";
            res[n-1]+=res[n];
            res.pop_back();
        }
        if(s=="-")
        {
            int n=res.size()-1;
            if(n<=0)throw "error";
            res[n-1]-=res[n];
            res.pop_back();
        }
        if(s=="*")
        {
            int n=res.size()-1;
            if(n<=0)throw "error";
            res[n-1]*=res[n];
            res.pop_back();
        }
        if(s=="/")
        {
            int n=res.size()-1;
            if(n<=0)throw "error";
            res[n-1]/=res[n];
            res.pop_back();
        }
        if(s=="^")
        {
            int n=res.size()-1;
            if(n<=0)throw "error";
            res[n-1]=power(res[n-1],res[n]);
            res.pop_back();
        }
    }
    if(res.size()!=1)throw "error";
    return res[0];
}
