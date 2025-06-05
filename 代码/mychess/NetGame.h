//NetGame.h
#ifndef NETGAME_H
#define NETGAME_H
#include"Board.h"
#include<QTcpServer>
#include<QTcpSocket>
class NetGame : public Board
{
    Q_OBJECT
public:
    NetGame(bool server);
    ~NetGame(){}
    QTcpServer* _server;
    QTcpSocket* _socket;
    void mouseReleaseEvent(QMouseEvent *ev);
    virtual void back();
    virtual void click(int selectid,int clickid,int row,int col);
    //virtual void isend();
public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETGAME_H
