#ifndef VOICE_H
#define VOICE_H

#include <QObject>
#include<QtMultimedia/QSound>
class Voice : public QObject
{
    Q_OBJECT
public:
    explicit Voice(QObject *parent = nullptr);
    ~Voice(){}

    QSound *_select=new QSound(":/new/prefix1/voice/selectChess.wav",this);
    QSound *_move =new QSound(":/new/prefix1/voice/moveChess.wav",this);
    QSound *_eat =new QSound(":/new/prefix1/voice/eatChess.wav",this);
    QSound *_end =new QSound(":/new/prefix1/voice/end.wav",this);
    QSound *_jiangjun =new QSound(":/new/prefix1/voice/jiangjun.wav",this);
    void voiceSelect(); //选棋音效
    void voiceMove();   //移动音效
    void voiceEat();    //吃子音效
    void voiceEnd();   //结束音效
    void voicejiangjun();//将军音效
signals:

};

#endif // VOICE_H
