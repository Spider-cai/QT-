//board.cpp
#include "Board.h"
#include<QPainter>
#include<QPoint>
#include<QMouseEvent>
#include<QDebug>
#include<QMessageBox>
#include<QPushButton>
Board::Board(QWidget *parent) : QWidget(parent)
{
    init(true);
    //redside=true;
}

void Board::init(bool bRedSide)
{
    for(int i=0; i<32; ++i)
    {
        _s[i].init(i);
    }
    if(bRedSide)
    {
        for(int i=0; i<32; ++i)
        {
            _s[i].rotate();
        }
    }

    _selectid = -1;
    redturn = true;
    redside = bRedSide;
    record[4]=-1;
    update();
}
void Board::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/new/prefix1/images/background.jpg"));
    //画棋盘
    for (int i=1;i<=10;i++){ //10根横线
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }
    for (int i=1;i<=9;i++){ //9根竖线
        if(i==1 || i==9) painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        else {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }
    }
    painter.drawLine(QPoint(4*d,d),QPoint(6*d,3*d));//老将九宫的斜线
    painter.drawLine(QPoint(6*d,d),QPoint(4*d,3*d));
    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(6*d,8*d),QPoint(4*d,10*d));

    //画棋子
    for (int i=0;i < 32; i++){
        drawStone(painter, i);
    }
    //QColor color(255, 0, 0);
    drawbotton(painter);
}
void Board::drawbotton(QPainter& painter){
    painter.setBrush(QBrush(QColor(242,247,247)));
    painter.drawRect(d,10.8*d,d*2,d*1);
    painter.setPen(Qt::black);
    painter.drawText(1.3*d,11.55*d, "悔棋");
    painter.setBrush(QBrush(QColor(242,247,247)));

    //

    if(_win==0) {
        painter.drawRect(7*d,10.8*d,d*2,d*1);
        painter.drawText(7.3*d,11.55*d, "认输");
    }
    else  if(_win==-1) {
        painter.drawRect(12*d,0*d,d*3.7,d*1.2);
        painter.drawText(12.2*d,0.9*d, "返回主菜单");
    }
}
QPoint Board::center(int row, int col){
    QPoint ret;
    ret.rx()=(col+1)*d;
    ret.ry()=(row+1)*d;
    return ret;
}

void Board::drawStone(QPainter& painter, int id){
    if(_s[id]._dead) return;
     QPoint c = center(_s[id]._row, _s[id]._col);
     QRect rect = QRect(c.x()-_r,c.y()-_r,d,d);

     if(id==_selectid) painter.setBrush(QBrush(QColor(245,247,175)));
     else painter.setBrush(QBrush(Qt::white));

     painter.setPen(Qt::black);

     painter.drawEllipse(center(_s[id]._row, _s[id]._col), _r, _r);

     if(_s[id]._red) painter.setPen(Qt::red);
     painter.drawEllipse(center(_s[id]._row, _s[id]._col), _r-2, _r-2);
     painter.setFont(QFont("MingLiU",_r-4,QFont::Bold));


     if(id<16)painter.drawText(rect,_s[id].gettext1(),QTextOption(Qt::AlignCenter));
     else if(id>=16)painter.drawText(rect,_s[id].gettext2(),QTextOption(Qt::AlignCenter));
}

void Board::back(){
    if(record[4]==-1){
        QMessageBox::about(NULL, "警告！", "不能连续悔棋！");
        return;
    }
    click(record[0],record[1],record[2],record[3]);
    record[4]=-1;
    update();
}

void Board::mouseReleaseEvent(QMouseEvent *ev){
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
        if(redturn) click(24,8,_s[8]._row,_s[8]._col);
        else click(8,24,_s[24]._row,_s[24]._col);
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
        v.voiceSelect();
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
                    click(_selectid,clickid,row,col);
                }
            }
            else{
                click(_selectid,clickid,row,col);
            }
        }
        _selectid=-1;
        update();
    }
}

void Board::click(int selectid,int clickid,int row,int col){
    record[0]=selectid;
    record[1]=clickid;
    record[2]=_s[selectid]._row;
    record[3]=_s[selectid]._col;
    record[4]=0;
    _s[selectid]._row=row;
    _s[selectid]._col=col;
    if(clickid!=-1) _s[clickid]._dead=not _s[clickid]._dead,v.voiceEat();else v.voiceMove();
    redturn=not redturn;

    isend();

    update();
    if(_win==-1) return;
    if(jiangjun()) v.voicejiangjun();
}

void Board::isend(){
    if(_s[8]._dead){
        v.voiceEnd();
        QMessageBox::about(NULL, "游戏结束", "黑方胜利！");
        _win=-1;
        return;
    }
    if(_s[24]._dead){
        v.voiceEnd();
        QMessageBox::about(NULL, "游戏结束", "红方胜利！");
        _win=-1;
        return;
    }
}
bool Board::jiangjun(){
    int row1=_s[8]._row,col1=_s[8]._col,row2=_s[24]._row,col2=_s[24]._col;
    if(not redturn){
        for (int i=0;i<=3;i++){
            if(_s[i]._dead==false) if(canmove(i,row2,col2)) return true;
        }
        for (int i=9;i<=15;i++) {
            if(_s[i]._dead==false) if(canmove(i,row2,col2)) return true;
        }
    }else{
        for (int i=0;i<=3;i++){
            if(_s[i+16]._dead==false) if(canmove(i+16,row1,col1)) return true;
        }
        for (int i=9;i<=15;i++) {
            if(_s[i+16]._dead==false) if(canmove(i+16,row1,col1)) return true;
        }
    }

    return false;
}

bool Board::getRowCol(QPoint pt, int &row, int &col){ //效率不高，可以改进,只判断四个角就可以了;

    for (row=0;row<=9;row++){
        for (col=0;col<=8;col++){
            QPoint c=center(row,col);
            int dx=c.x()-pt.x();
            int dy=c.y()-pt.y();
            int dist=dx*dx+dy*dy;
            if(dist<_r*_r){
                return true;
            }
        }
    }
    return false;
}

bool Board::exist(int row,int col){
    for (int i=0;i<32;i++) if(_s[i]._row==row && _s[i]._col==col && _s[i]._dead==false) return true;
    return false;
}

bool Board::caneat(int selectid,int clickid){
    if(_s[selectid]._red==_s[clickid]._red) return false;
    else return true;
}
bool Board::canmove(int selectid,int row,int col){
    switch (_s[selectid]._type){
        case Stone::CHE:
            return canmove_CHE(selectid, row, col);
        case Stone::MA:
            return canmove_MA(selectid, row, col);
        case Stone::PAO:
            return canmove_PAO(selectid, row, col);
        case Stone::BING:
            return canmove_BING(selectid, row, col);
        case Stone::XIANG:
            return canmove_XIANG(selectid, row, col);
        case Stone::SHI:
            return canmove_SHI(selectid, row, col);
        case Stone::JIANG:
            return canmove_JIANG(selectid, row, col);
    }
}

bool Board::canmove_CHE(int selectid,int row,int col){
    int row1=_s[selectid]._row;
    int col1=_s[selectid]._col;
    if((row == row1 && col!=col1) || (row!=row1 && col==col1)) {
        if(row==row1){
            if(col>col1){
                int temp=col;
                col=col1;
                col1=temp;
            }
            for (int i=col+1;i<col1;i++){
                if(exist(row,i)){
                    return false;
                }
            }
            return true;
        }
        else{
            if(row>row1){
                int temp=row;
                row=row1;
                row1=temp;
            }
            for (int i=row+1;i<row1;i++){
                if(exist(i,col)){
                    return false;
                }
            }
            return true;
        }
    }
    else return false;
}

bool Board::canmove_MA(int selectid,int row,int col){
    int row1=_s[selectid]._row;
    int col1=_s[selectid]._col;
    bool u=exist(row1,col1+1), d=exist(row1,col1-1),l=exist(row1-1,col1),r=exist(row1+1,col1);
    if(row==row1+1 && col==col1+2 && !u) return true;
    if(row==row1-1 && col==col1+2 && !u) return true;
    if(row==row1+1 && col==col1-2 && !d) return true;
    if(row==row1-1 && col==col1-2 && !d) return true;
    if(row==row1-2 && col==col1-1 && !l) return true;
    if(row==row1-2 && col==col1+1 && !l) return true;
    if(row==row1+2 && col==col1-1 && !r) return true;
    if(row==row1+2 && col==col1+1 && !r) return true;
    return false;
}
bool Board::canmove_PAO(int selectid,int row,int col){
    int cnt=0;
    int row1=_s[selectid]._row;
    int col1=_s[selectid]._col;
    int r=row,c=col;
    if((row == row1 && col!=col1) || (row!=row1 && col==col1)) {
        if(row==row1){
            if(col>col1){
                col=col^col1;
                col1=col^col1;
                col=col^col1;
            }
            for (int i=col+1;i<col1;i++){
                if(exist(row,i)){
                    cnt++;
                }
            }
            bool ee=exist(r,c);
            if(cnt==0 && !ee)return true;
            if(cnt==1 && ee) return true;
            return false;
        }
        else{
            if(row>row1){
                row=row^row1;
                row1=row^row1;
                row=row^row1;
            }
            for (int i=row+1;i<row1;i++){
                if(exist(i,col)){
                    cnt++;
                }
            }
            bool ee=exist(r,c);
            if(cnt==0 && !ee)return true;
            if(cnt==1 && ee) return true;
            return false;
        }
    }
    else return false;
}
bool Board::canmove_BING(int selectid,int row,int col){
    int row1=_s[selectid]._row;
    int col1=_s[selectid]._col;
    if(!this->redside){
        if(_s[selectid]._red){
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
    else{
        if(!_s[selectid]._red){
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
}
bool Board::canmove_XIANG(int selectid,int row,int col){
    int row1=_s[selectid]._row;
    int col1=_s[selectid]._col;
    bool ul=exist(row1-1,col1-1),ur=exist(row1-1,col1+1),dl=exist(row1+1,col1-1),dr=exist(row1+1,col1+1);
    if(!this->redside){
        if(_s[selectid]._red){
            if(row>4) return false;
        } else if(row<5) return false;
    }
    else{
        if(_s[selectid]._red){
            if(row<5) return false;
        } else if(row>4) return false;
    }
    if(row==row1-2 && col==col1-2 && !ul) return true;
    if(row==row1-2 && col==col1+2 && !ur) return true;
    if(row==row1+2 && col==col1-2 && !dl) return true;
    if(row==row1+2 && col==col1+2 && !dr) return true;
    return false;
}
bool Board::canmove_SHI(int selectid,int row,int col){
    int row1=_s[selectid]._row;
    int col1=_s[selectid]._col;
    if(!this->redside){
        if(_s[selectid]._red){
            if(row>2) return false;
        }
        else{
            if(row<7) return false;
        }
    }
    else{
        if(_s[selectid]._red){
            if(row<7) return false;
        }
        else{
            if(row>2) return false;
        }
    }
    if(col<3 || col>5) return false;
    if(row==row1+1 && col==col1+1) return true;
    if(row==row1-1 && col==col1+1) return true;
    if(row==row1+1 && col==col1-1) return true;
    if(row==row1-1 && col==col1-1) return true;
    return false;
}
bool Board::canmove_JIANG(int selectid,int row,int col){
    int row1=_s[selectid]._row;
    int col1=_s[selectid]._col;

    if(col1==col){
        if(row>row1){
            int temp=row;
            row=row1;
            row1=temp;
        }
        bool ee=true;
        for (int i=row+1;i<row1;i++){
            if(exist(i,col)){
                ee=false;
            }
        }
        if(ee) return true;
    }

    if(!this->redside){
        if(_s[selectid]._red){
            if(row>2) return false;
        }
        else{
            if(row<7) return false;
        }
    }
    else{
        if(_s[selectid]._red){
            if(row<7) return false;
        }
        else{
            if(row>2) return false;
        }
    }
    if(col<3 || col>5) return false;
    if(row==row1+1 && col==col1) return true;
    if(row==row1-1 && col==col1) return true;
    if(row==row1 && col==col1-1) return true;
    if(row==row1 && col==col1+1) return true;
    return false;

}


























