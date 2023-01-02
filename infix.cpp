#include "infix.h"

Infix_Expression::Infix_Expression(Infix_Expression &p)
{
    expression=p.expression;
}

Infix_Expression::Infix_Expression(string _expression)
{
    expression=_expression;
}

void Infix_Expression::Postfix_to_Infix(vector<string>str)
{
    vector<string>sta;
    vector<int>id;//1(+-) 2(*/) 3(^) 4(()number)

    for(string s:str)
    {
        if(s[0]>='0'&&s[0]<='9')
        {
            sta.push_back(s);
            id.push_back(4);
        }
        if(s=="+")
        {
            int n=sta.size()-1;
            sta[n-1]+="+"+sta[n];
            id[n-1]=1;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="-")
        {
            int n=sta.size()-1;
            sta[n-1]+="-"+sta[n];
            id[n-1]=1;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="*")
        {
            int n=sta.size()-1;
            if(id[n-1]==1)
            {
                sta[n-1]="("+sta[n-1]+")";
            }
            if(id[n]==1)
            {
                sta[n]="("+sta[n]+")";
            }
            sta[n-1]+="*"+sta[n];
            id[n-1]=2;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="/")
        {
            int n=sta.size()-1;
            if(id[n-1]==1)
            {
                sta[n-1]="("+sta[n-1]+")";
            }
            if(id[n]==1)
            {
                sta[n]="("+sta[n]+")";
            }
            sta[n-1]+="/"+sta[n];
            id[n-1]=2;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="^")
        {
            int n=sta.size()-1;
            if(id[n-1]<=2)
            {
                sta[n-1]="("+sta[n-1]+")";
            }
            if(id[n]<=2)
            {
                sta[n]="("+sta[n]+")";
            }
            sta[n-1]+="^"+sta[n];
            id[n-1]=3;
            sta.pop_back();
            id.pop_back();
        }
    }
    expression=sta[0];
    change();
}

void Infix_Expression::Prefix_to_Infix(vector<string>str)
{
    vector<string>sta;
    vector<int>id;//1(+-) 2(*/) 3(^) 4(()number)

    reverse(str.begin(),str.end());
    for(string s:str)
    {
        if(s[0]>='0'&&s[0]<='9')
        {
            reverse(s.begin(),s.end());
            sta.push_back(s);
            id.push_back(4);
        }
        if(s=="+")
        {
            int n=sta.size()-1;
            sta[n-1]=sta[n]+"+"+sta[n-1];
            id[n-1]=1;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="-")
        {
            int n=sta.size()-1;
            sta[n-1]=sta[n]+"-"+sta[n-1];
            id[n-1]=1;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="*")
        {
            int n=sta.size()-1;
            if(id[n-1]==1)
            {
                sta[n-1]="("+sta[n-1]+")";
            }
            if(id[n]==1)
            {
                sta[n]="("+sta[n]+")";
            }
            sta[n-1]=sta[n]+"*"+sta[n-1];
            id[n-1]=2;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="/")
        {
            int n=sta.size()-1;
            if(id[n-1]==1)
            {
                sta[n-1]="("+sta[n-1]+")";
            }
            if(id[n]==1)
            {
                sta[n]="("+sta[n]+")";
            }
            sta[n-1]=sta[n]+"/"+sta[n-1];
            id[n-1]=2;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="^")
        {
            int n=sta.size()-1;
            if(id[n-1]<=2)
            {
                sta[n-1]="("+sta[n-1]+")";
            }
            if(id[n]<=2)
            {
                sta[n]="("+sta[n]+")";
            }
            sta[n-1]=sta[n]+"^"+sta[n-1];
            id[n-1]=3;
            sta.pop_back();
            id.pop_back();
        }
    }
    expression=sta[0];
    change();
}
