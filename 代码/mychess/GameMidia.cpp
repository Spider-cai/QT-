//GameMidia.cpp
#include "GameMidia.h"

GameMidia::GameMidia(QString address,QObject *parent) : QObject(parent)
{
    this->media=new QMediaPlayer(this);
    this->setParent(parent);
    this->path=address;
    this->media->setVolume(20);
}

void GameMidia::ForeverPlay(){
    QTimer* timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        if(this->media->state()!= QMediaPlayer::PlayingState){
            QFile* file=new QFile(this->path);
            if(!file->open(QIODevice::ReadOnly)){
                qDebug()<<"open error!";
                return;
            }
            this->media->setMedia(QMediaContent(),file);
            this->media->setVolume(20);
            this->media->play();
        }
    });
    timer->start(10);
}
