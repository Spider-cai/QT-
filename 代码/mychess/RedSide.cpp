#include "RedSide.h"
#include<QPainter>
#include<QPoint>
#include<QMouseEvent>
RedSide::RedSide(QWidget *parent):Board(parent)
{
    m_tcpServer = NULL;
    m_tcpSocket = NULL;
    m_tcpServer = new QTcpServer(this);
    m_tcpServer->listen(QHostAddress::Any, 9999);
    connect(m_tcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
    /*
    for (int i=0;i<32;i++){
        _s[i].init(i);
    }
    _selectid=-1;
    redturn=true;
    */


    for (int i=0;i<32;i++){
        _s[i]._red=not _s[i]._red;
    }
}

bool RedSide::canmove_BING(int selectid,int row,int col){
    int row1=_s[selectid]._row;
    int col1=_s[selectid]._col;
    if(not _s[selectid]._red){
        if(_s[selectid]._row<=4){
            if(col==col1 && row==row1+1) return true;
            else return false;
        }
        else{
            if(col==col1 && row==row1+1) return true;
            if(row==row1 && col==col1-1) return true;
            if(row==row1 && col==col1+1) return true;
            return false;
        }
    }
    else {
        if(_s[selectid]._row>=5){
            if(col==col1 && row==row1-1) return true;
            else return false;
        }
        else{
            if(col==col1 && row==row1-1) return true;
            if(row==row1 && col==col1-1) return true;
            if(row==row1 && col==col1+1) return true;
            return false;
        }
    }
}


void RedSide::mouseReleaseEvent(QMouseEvent *ev){
    if(redturn){
        QPoint pt = ev->pos();
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
            if(clickid!=-1 && redturn==_s[clickid]._red) {
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
                        RedSide::click(clickid,row,col);
                    }
                }
                else{
                    RedSide::click(clickid,row,col);
                }
            }
            _selectid=-1;
            update();
        }
    }
}

bool RedSide::click(int clickid,int row,int col){
    Board::click(clickid, row, col);
    char arry[3];
    arry[0] = clickid;
    arry[1] = row;
    arry[2] = col;
    m_tcpSocket->write(arry, 3);
}

void RedSide::slotNewConnection()
{

    m_tcpSocket = m_tcpServer->nextPendingConnection();
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecv()));
}

void RedSide::slotRecv()
{
    QByteArray arry = m_tcpSocket->readAll();

    int nCheckedID = arry[0];
    int nRow = arry[1];
    int nCol = arry[2];

    qDebug()<<nCheckedID<<"   "<<nRow<<"   "<<nCol<<"   ";
    Board::click(nCheckedID, nRow, nCol);
}








