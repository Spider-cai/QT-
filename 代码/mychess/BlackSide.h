#ifndef BLACKSIDE_H
#define BLACKSIDE_H
#include<QObject>
#include"Board.h"
#include <QTcpServer>
#include <QTcpSocket>
class BlackSide : public Board
{

public:
    explicit BlackSide(QWidget *parent = 0);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual bool click(int clickid,int row,int col);
    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;
public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // BLACKSIDE_H
