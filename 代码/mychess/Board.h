//board.h
#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"
#include"Voice.h"
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    Stone _s[32];
    int d=40;
    int _r=d/2;
    int _selectid;
    bool redturn;
    QPoint center(int row,int col);
    void drawStone(QPainter& painter, int id);
    void paintEvent(QPaintEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    bool getRowCol(QPoint pt, int& row,int& col);
    bool canmove(int selectid,int row,int col);
    bool caneat(int selectid,int clickid);
    bool canmove_CHE(int selectid,int row,int col);
    bool canmove_MA(int selectid,int row,int col);
    bool canmove_PAO(int selectid,int row,int col);
    bool canmove_BING(int selectid,int row,int col);
    bool canmove_XIANG(int selectid,int row,int col);
    bool canmove_SHI(int selectid,int row,int col);
    bool canmove_JIANG(int selectid,int row,int col);
    bool exist(int row, int col);
    virtual void click(int selectid,int clickid,int row,int col);
    bool redside=true;
    virtual void back();
    void init(bool bRedSide);
    Voice v;
    void drawbotton(QPainter& painter);
    int _win=0;
    int record[5];
    bool jiangjun();
    virtual void isend();
signals:
    void endd();
};

#endif // BOARD_H
