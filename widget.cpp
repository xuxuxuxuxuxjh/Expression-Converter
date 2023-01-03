#include "widget.h"
#include "ui_widget.h"
#include "function.h"
#include<qdebug.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("计算器");

    QFont f("仿宋",14);
    ui->mainLineEdit_prefix->setFont(f);
    ui->mainLineEdit_infix->setFont(f);
    ui->mainLineEdit_postfix->setFont(f);

    //QIcon con("C:\\Qt\\xucode\\calc2\\del.png");
    //ui->ButtonDel->setIcon(con);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Insert(char ch)
{
    if(status==1)
    {
        prefix.expression+=ch;
        ui->mainLineEdit_prefix->setText(str_to_qstr(prefix.expression));
    }
    if(status==2)
    {
        infix.expression+=ch;
        ui->mainLineEdit_infix->setText(str_to_qstr(infix.expression));
    }
    if(status==3)
    {
        postfix.expression+=ch;
        ui->mainLineEdit_postfix->setText(str_to_qstr(postfix.expression));
    }
}



void Widget::on_pushButton_prefix_clicked()
{
    status=1;
    on_ButtonClear_clicked();
}

void Widget::on_pushButton_infix_clicked()
{
    status=2;
    on_ButtonClear_clicked();
}

void Widget::on_pushButton_postfix_clicked()
{
    status=3;
    on_ButtonClear_clicked();
}



void Widget::on_Button0_clicked()
{
    Insert('0');
}

void Widget::on_Button1_clicked()
{
    Insert('1');
}

void Widget::on_Button2_clicked()
{
    Insert('2');
}

void Widget::on_Button3_clicked()
{
    Insert('3');
}

void Widget::on_Button4_clicked()
{
    Insert('4');
}

void Widget::on_Button5_clicked()
{
    Insert('5');
}

void Widget::on_Button6_clicked()
{
    Insert('6');
}

void Widget::on_Button7_clicked()
{
    Insert('7');
}

void Widget::on_Button8_clicked()
{
    Insert('8');
}

void Widget::on_Button9_clicked()
{
    Insert('9');
}

void Widget::on_ButtonPoint_clicked()
{
    Insert('.');
}

void Widget::on_ButtonWS_clicked()
{
    Insert(' ');
}

void Widget::on_ButtonAdd_clicked()
{
    Insert('+');
}

void Widget::on_ButtonSub_clicked()
{
    Insert('-');
}

void Widget::on_ButtonMul_clicked()
{
    Insert('*');
}

void Widget::on_ButtonDiv_clicked()
{
    Insert('/');
}

void Widget::on_ButtonPower_clicked()
{
    Insert('^');
}

void Widget::on_ButtonL_clicked()
{
    Insert('(');
}

void Widget::on_ButtonR_clicked()
{
    Insert(')');
}

void Widget::on_ButtonClear_clicked()
{
    prefix.expression="";
    ui->mainLineEdit_prefix->setText(str_to_qstr(prefix.expression));

    infix.expression="";
    ui->mainLineEdit_infix->setText(str_to_qstr(infix.expression));

    postfix.expression="";
    ui->mainLineEdit_postfix->setText(str_to_qstr(postfix.expression));
}

void Widget::on_ButtonDel_clicked()
{
    if(status==1)
    {
        if(!prefix.expression.empty())
            prefix.expression.pop_back();
        ui->mainLineEdit_prefix->setText(str_to_qstr(prefix.expression));
    }
    if(status==2)
    {
        if(!infix.expression.empty())
            infix.expression.pop_back();
        ui->mainLineEdit_infix->setText(str_to_qstr(infix.expression));
    }
    if(status==3)
    {
        if(!postfix.expression.empty())
            postfix.expression.pop_back();
        ui->mainLineEdit_postfix->setText(str_to_qstr(postfix.expression));
    }
}



void Widget::on_ButtonSin_clicked()
{
    try{
        Widget::on_ButtonEquel_clicked();
        double val=str_to_double(infix.expression);
        val=sin(val);
        infix.expression=double_to_str(val);
        ui->mainLineEdit_infix->setText(str_to_qstr(infix.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
//        throw;
    }
}

void Widget::on_ButtonCos_clicked()
{
    try{
        Widget::on_ButtonEquel_clicked();
        double val=str_to_double(infix.expression);
        val=cos(val);
        infix.expression=double_to_str(val);
        ui->mainLineEdit_infix->setText(str_to_qstr(infix.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
//        throw;
    }
}

void Widget::on_ButtonDao_clicked()
{
    try{
        Widget::on_ButtonEquel_clicked();
        double val=str_to_double(infix.expression);
        val=1.0/val;
        infix.expression=double_to_str(val);
        ui->mainLineEdit_infix->setText(str_to_qstr(infix.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
//        throw;
    }
}



void Widget::on_ButtonEquel_clicked()
{
    try{
        Postfix_Expression post;
        infix.change();
        post.Infix_to_Postfix(infix.str_expression);
        infix.expression=double_to_str(post.calculation());
        ui->mainLineEdit_infix->setText(str_to_qstr(infix.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
    }
}



void Widget::on_pushButton_prefix_to_infix_clicked()//前缀表达式转中缀表达式
{
    try{
        Infix_Expression in;
        prefix.change();
        in.Prefix_to_Infix(prefix.str_expression);
        ui->mainLineEdit_infix->setText(str_to_qstr(in.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
    }
}

void Widget::on_pushButton_prefix_to_postfix_clicked()//前缀表达式转后缀表达式
{
    try{
        Postfix_Expression post;
        prefix.change();
        post.Prefix_to_Postfix(prefix.str_expression);
        ui->mainLineEdit_postfix->setText(str_to_qstr(post.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
    }
}

void Widget::on_pushButton_infix_to_prefix_clicked()//中缀表达式转前缀表达式
{
    try{
        Prefix_Expression pre;
        infix.change();
        pre.Infix_to_Prefix(infix.str_expression);
        ui->mainLineEdit_prefix->setText(str_to_qstr(pre.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
    }
}

void Widget::on_pushButton_infix_to_postfix_clicked()//中缀表达式转后缀表达式
{
    try{
        Postfix_Expression post;
        infix.change();
        post.Infix_to_Postfix(infix.str_expression);
        ui->mainLineEdit_postfix->setText(str_to_qstr(post.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
    }
}

void Widget::on_pushButton_postfix_to_prefix_clicked()//后缀表达式转前缀表达式
{
    try{
        Prefix_Expression pre;
        postfix.change();
        pre.Postfix_to_Prefix(postfix.str_expression);
        ui->mainLineEdit_prefix->setText(str_to_qstr(pre.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
    }
}

void Widget::on_pushButton_postfix_to_infix_clicked()//后缀表达式转中缀表达式
{
    try{
        Infix_Expression in;
        postfix.change();
        in.Postfix_to_Infix(postfix.str_expression);
        ui->mainLineEdit_infix->setText(str_to_qstr(in.expression));
    }catch(...){
        on_ButtonClear_clicked();
        ui->mainLineEdit_infix->setText(str_to_qstr("Wrong Expression"));
    }
}
