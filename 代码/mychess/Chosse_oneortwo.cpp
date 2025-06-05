//Choose_oneortwo.cpp
#include "Chosse_oneortwo.h"
#include "ui_chosse_oneortwo.h"
#include<QDebug>
Chosse_oneortwo::Chosse_oneortwo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chosse_oneortwo)
{
    ui->setupUi(this);
}

Chosse_oneortwo::~Chosse_oneortwo()
{
    delete ui;
}

void Chosse_oneortwo::on_pushButton_released()
{
    e=true;
    accept();
}

void Chosse_oneortwo::on_pushButton_2_released()
{
    e=false;
    accept();
}

/*
void Chosse_oneortwo::on_pushButton_3_released()
{
    qDebug()<<"backtomenu is clicked";
    emit this->backtomenu();
}
*/
