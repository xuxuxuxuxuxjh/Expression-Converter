#include "infix.h"

Infix_Expression::Infix_Expression(Infix_Expression &p)
{
    expression=p.expression;
}

Infix_Expression::Infix_Expression(string _expression)
{
    expression=_expression;
}

void Infix_Expression::change()
{
    string number="";
    int flag=0;//flag=0表示前一个字符不是)或是数字
    this->str_expression.clear();
    for(char ch:expression)
    {
        if((ch>='0'&&ch<='9')||ch=='.')
        {
            number=number+ch;
            flag=1;
        }
        else{
            if(number!="")this->str_expression.push_back(number);
            number="";
            if(ch==' ')continue;
            if(ch=='-'&&flag==0)number+='-';//是负号而不是减号
            else{
                string s="";
                s+=ch;
                this->str_expression.push_back(s);
            }
            if(ch==')')flag=1;
            else flag=0;
        }
    }
    if(number!="")
        this->str_expression.push_back(number);
    if(!check())throw "error";
}

void Infix_Expression::Postfix_to_Infix(vector<string>str)
{
    vector<string>sta;
    vector<int>id;//1(+-) 2(*/) 3(^) 4(()number)

    for(string s:str)
    {
        if((s[0]>='0'&&s[0]<='9')||s.size()>1)
        {
            sta.push_back(s);
            id.push_back(4);
        }
        if(s=="+")
        {
            int n=sta.size()-1;
            if(n<=0)throw "error";
            sta[n-1]+="+"+sta[n];
            id[n-1]=1;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="-")
        {
            int n=sta.size()-1;
            if(n<=0)throw "error";
            sta[n-1]+="-"+sta[n];
            id[n-1]=1;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="*")
        {
            int n=sta.size()-1;
            if(n<=0)throw "error";
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
            if(n<=0)throw "error";
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
            if(n<=0)throw "error";
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
    if(sta.size()!=1)throw "error";
    this->expression=sta[0];
    try{
        this->change();
    }catch(...){
        throw "error";
    }
}

void Infix_Expression::Prefix_to_Infix(vector<string>str)
{
    vector<string>sta;
    vector<int>id;//1(+-) 2(*/) 3(^) 4(()number)

    reverse(str.begin(),str.end());
    for(string s:str)
    {
        if((s[0]>='0'&&s[0]<='9')||s.size()>1)
        {
            sta.push_back(s);
            id.push_back(4);
        }
        if(s=="+")
        {
            int n=sta.size()-1;
            if(n<=0)throw "error";
            sta[n-1]=sta[n]+"+"+sta[n-1];
            id[n-1]=1;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="-")
        {
            int n=sta.size()-1;
            if(n<=0)throw "error";
            sta[n-1]=sta[n]+"-"+sta[n-1];
            id[n-1]=1;
            sta.pop_back();
            id.pop_back();
        }
        if(s=="*")
        {
            int n=sta.size()-1;
            if(n<=0)throw "error";
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
            if(n<=0)throw "error";
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
            if(n<=0)throw "error";
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
    if(sta.size()!=1)throw "error";
    this->expression=sta[0];
    try{
        this->change();
    }catch(...){
        throw "error";
    }
}
