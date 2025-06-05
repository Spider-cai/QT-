#ifndef REDSIDE_H
#define REDSIDE_H
#include<QObject>
#include"Board.h"
#include <QTcpServer>
#include <QTcpSocket>
class RedSide : public Board
{
public:
    explicit RedSide(QWidget *parent = 0);
    bool canmove_BING(int selectid,int row,int col);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual bool click(int clickid,int row,int col);
    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;
public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // REDSIDE_H
