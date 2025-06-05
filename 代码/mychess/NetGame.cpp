//NetGame.cpp
#include "NetGame.h"
#include<QDebug>
#include<QPoint>
#include<QMouseEvent>
#include<QMessageBox>

NetGame::NetGame(bool server)
{
    _server=NULL;
    _socket=NULL;
    if(server){
        _server=new QTcpServer(this);
        _server->listen(QHostAddress::Any,9989);
        connect(_server,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    }else{
        _socket=new QTcpSocket(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"),9989); //能实现局域网内的联机（如手机热点）
        //127.0.0.1               本机地址
        //192.168.167.79          我电脑连上手机热点时的IPV4地址
        //10.255.47.76            校园网IPV4地址，已测，连接不成功
        connect(_socket,SIGNAL(readyRead()),this,SLOT(slotRecv()));
    }
}

void NetGame::click(int selectid,int clickid,int row,int col){
    Board::click(selectid,clickid,row,col);
    char buf[5];
    buf[0]=2;
    buf[1]=9-row;
    buf[2]=8-col;
    buf[3]=clickid;
    buf[4]=selectid;
    _socket->write(buf,5);
    update();
}
/*
void NetGame::isend(){
    if(_s[8]._dead){
        v.voiceEnd();
        if(redside)QMessageBox::about(NULL, "游戏结束", "胜败乃兵家常事，再接再厉！");
        else QMessageBox::about(NULL, "游戏结束", "恭喜你获得胜利！");
        _win=-1;
        return;
    }
    if(_s[24]._dead){
        v.voiceEnd();
        if(!redside)QMessageBox::about(NULL, "游戏结束", "胜败乃兵家常事，再接再厉！");
        else QMessageBox::about(NULL, "游戏结束", "恭喜你获得胜利！");
        _win=-1;
        return;
    }
}*/
void NetGame::back(){           //悔棋
    if(record[4]==-1){
        QMessageBox::about(NULL, "警告！", "不能连续悔棋！");
        return;
    }
    click(record[0],record[1],record[2],record[3]);
    record[4]=-1;
    update();
}
void NetGame::slotNewConnection(){   //服务器检测到有客户端连接时进入的函数
    if(_socket!=NULL) return;
    _socket=_server->nextPendingConnection();
    connect(_socket,SIGNAL(readyRead()),this,SLOT(slotRecv()));
    char buf[2];
    buf[0]=1;
    buf[1]=0;
    _socket->write(buf,2);
    init(buf[1]==0);
}
void NetGame::slotRecv(){          //收到->write发出的信号之后进入函数
    QByteArray ba=_socket->readAll();
    char cmd=ba[0];
    if(cmd==1){
        qDebug()<<5;
        char data=ba[1];
        init(data==1);
    }
    if(cmd==2){
        qDebug()<<4;
        int row=ba[1];
        int col=ba[2];
        int id=ba[3];
        int s=ba[4];
        Board::click(s,id,row,col);
    }
}


void NetGame::mouseReleaseEvent(QMouseEvent *ev){
    QPoint pt = ev->pos();
    if(pt.rx()>=12*d && pt.rx()<=15.7*d && pt.ry()>=0 && pt.ry()<=1.2*d){
        if(_win==0) return;
        emit this->endd();
    }
    if(_win==-1) return;

    if(pt.rx()>=d && pt.rx()<=3*d && pt.ry()>=10.8*d && pt.ry()<=11.8*d){
        back();
    }

    if(pt.rx()>=7*d && pt.rx()<=9*3*d && pt.ry()>=10.8*d && pt.ry()<=11.8*d){
        if(redside) NetGame::click(24,8,_s[8]._row,_s[8]._col);
        else NetGame::click(8,24,_s[24]._row,_s[24]._col);
    }
    //将pt转化成象棋的行列值
    //判断这个行列值上面有没有棋子
    //如果有棋子就把它选中
    int row, col, i, clickid=-1;
    bool bRet=getRowCol(pt,row,col);
    if(bRet==false) return;//点到棋盘外了
    for (i=0;i<32;++i){
        if(_s[i]._row==row && _s[i]._col==col && _s[i]._dead==false){
            break;
        }
    }
    if(i<32) {
        clickid=i;
        update();
    }
    if(_selectid==-1){
        if(i<16 && redside==false) return;
        if(i>=16 && redside==true) return;
        if(clickid!=-1 && redturn==_s[clickid]._red) {
            v.voiceSelect();
            _selectid=clickid;
            update();
        }
    }
    else {
        /*_s[_selectid]._row=row;
        _s[_selectid]._col=col;
        if(clickid!=-1){
            _s[clickid]._dead=true;
        }
        _selectid=-1;
        update();*/
        if(canmove(_selectid,row,col)){
            if(clickid!=-1){
                if(caneat(_selectid,clickid)){
                    click(_selectid,clickid,row,col);
                    update();
                }
            }
            else{
                click(_selectid,clickid,row,col);
                update();
            }
        }
        _selectid=-1;
        update();
    }
}



















