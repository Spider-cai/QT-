//begin.h
#include <QDialog>

#include"NetGame.h"
#include "Chosse_oneortwo.h"
namespace Ui {
class Begin;
}

class Begin : public QDialog
{
    Q_OBJECT

public:
    explicit Begin(QWidget *parent = nullptr);
    ~Begin();
    int s;
private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

private:
    Ui::Begin *ui;
    Board *SigleGame;
    NetGame *DoubleGame;
    Chosse_oneortwo *c;
};


