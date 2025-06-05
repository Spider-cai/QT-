//Choose_oneortwo.h
#ifndef CHOSSE_ONEORTWO_H
#define CHOSSE_ONEORTWO_H

#include <QDialog>

namespace Ui {
class Chosse_oneortwo;
}

class Chosse_oneortwo : public QDialog
{
    Q_OBJECT

public:
    explicit Chosse_oneortwo(QWidget *parent = nullptr);
    ~Chosse_oneortwo();
    bool e;
signals:
    void backtomenu();
//    void P1();
//    void P2();
private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    //void on_pushButton_3_released();

private:
    Ui::Chosse_oneortwo *ui;

};

#endif // CHOSSE_ONEORTWO_H
