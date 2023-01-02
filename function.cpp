#include "function.h"

long long str_to_int(string s)//用乘权累加法将string转化为int
{
    long long res=0;
    for(char ch:s)
    {
        res=res*10+ch-48;
    }
    return res;
}

double str_to_double(string s)//将string转化为double
{
    int n=s.size();
    int pos=0;
    for(int i=0;i<n;i++)
        if(s[i]=='.')pos=i;
    if(pos==0)
    {
        double res=1.0;
        res=res*str_to_int(s);
        return res;
    }
    else{
        double res1=1.0,res2=1.0;
        string int_part="",double_part="";
        for(int i=0;i<pos;i++)
        {
            int_part+=s[i];
        }
        for(int i=pos+1;i<n;i++)
        {
            double_part+=s[i];
            res2=res2*0.1;
        }
        res1=res1*str_to_int(int_part);
        res2=res2*str_to_int(double_part);
        return res1+res2;
    }
}

string double_to_str(double lf)//将double转为string,保留5位小数
{
    string res="";
    int number=(int)(lf*100000);
    vector<char>ch;

    if(number==0)
    {
        res="0";
        return res;
    }
    if(number<0)
    {
        res="-";
        number=-number;
    }
    while(number>0)
    {
        ch.push_back((char)(number%10+48));
        number/=10;
    }
    
    int n=ch.size();
    reverse(ch.begin(),ch.end());
    if(n<=5)res+="0";
    for(int i=1;i<=n-5;i++)
    {
        res+=ch[i-1];
    }
    res+=".";
    for(int i=n-4;i<=n;i++)
    {
        res+=ch[i-1];
    }
    for(int i=1;i<=5;i++)
    {
        int len=res.size();
        if(res[len-1]=='0')res.pop_back();
    }
    int len=res.size();
    if(res[len-1]=='.')res.pop_back();
    return res;
}

QString str_to_qstr(string s)
{
    QString res="";
    for(char ch:s)
    {
        res+=ch;
    }
    return res;
}

double kuai(double a,double b)//用快速幂的方法计算幂a^b
{
    double res=1.0;
    int number=(int)b;
    while(number>0)
    {
        if(number&1)res=res*a;
        a=a*a;
        number=number/2;
    }
    return res;
}
