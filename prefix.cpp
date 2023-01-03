#include "prefix.h"
#include "infix.h"

Prefix_Expression::Prefix_Expression(Prefix_Expression &p)
{
    expression=p.expression;
}

Prefix_Expression::Prefix_Expression(string _expression)
{
    expression=_expression;
}

void Prefix_Expression::Infix_to_Prefix(vector<string>str)
{
    stack<string>sta;
    vector<string>res;
    reverse(str.begin(),str.end());
    for(string s:str)
    {
        if((s[0]>='0'&&s[0]<='9')||s.size()>1)res.push_back(s);
        if(s==")")sta.push(s);
        if(s=="+"||s=="-")
        {
            while(!sta.empty()&&sta.top()!=")")
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
        if(s=="(")
        {
            while(!sta.empty()&&sta.top()!=")")
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
    reverse(res.begin(),res.end());
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

void Prefix_Expression::Postfix_to_Prefix(vector<string>str)
{
    try{
        //后缀转中缀
        Infix_Expression infix;
        infix.Postfix_to_Infix(str);
        infix.change();

        //中缀转前缀
        Infix_to_Prefix(infix.str_expression);
        this->change();
    }catch(...){
        throw "error";
    }
}
