#ifndef CHOOSEDLG_H
#define CHOOSEDLG_H

#include <QObject>

#include <QDialog>
#include <QPushButton>

class ChooseDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseDlg(QWidget *parent = 0);
    ~ChooseDlg();

    QPushButton* _buttons[2];
    int _selected=5;
signals:

public slots:
    void slotClicked();
};

#endif // CHOOSEDLG_H
