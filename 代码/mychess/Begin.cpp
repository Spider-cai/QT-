//begin.cpp
#include "Begin.h"
#include "ui_Begin.h"
#include<QMessageBox>


Begin::Begin(QWidget *parent) : QDialog(parent),ui(new Ui::Begin)
{
    ui->setupUi(this);
}

Begin::~Begin()
{
    delete ui;
}

void Begin::on_pushButton_released()
{
    this->hide();
    SigleGame =new Board();
    SigleGame->show();
    connect(SigleGame,&Board::endd,[=](){
        SigleGame->close();
        this->show();
    });
}

void Begin::on_pushButton_2_released()
{
    this->hide();
    c = new Chosse_oneortwo() ;
    c->exec();
    bool e=c->e;
//    connect(c, &Chosse_oneortwo::backtomenu,[=](){
//        qDebug()<<"this->show";
//        c->accept();
//        this->show();
//    });
    /*
    setbuf(stdout, NULL);
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(NULL,"red or black","是否执红");
    if(ret==QMessageBox::Yes){
        e=true;
    }

    connect(c,&Chosse_oneortwo::P1,[=](){
        DoubleGame=new NetGame(true);
        DoubleGame->show();
    });
    connect(c,&Chosse_oneortwo::P2,[=](){
        DoubleGame=new NetGame(false);
        DoubleGame->show();
    });*/
    DoubleGame= new NetGame(e);
    DoubleGame->show();
    connect(DoubleGame,&Board::endd,[=](){
        DoubleGame->close();
        this->show();
    });
}

void Begin::on_pushButton_3_released()
{
    this->s=3;
    accept();
}
