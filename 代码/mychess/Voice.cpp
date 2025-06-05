#include "Voice.h"
#include<QObject>

Voice::Voice(QObject *parent) : QObject(parent)
{

}

void Voice::voiceSelect()
{
    if(_select!= nullptr)
        this->_select->play();
}

void Voice:: voiceMove()
{
    if(_move!= nullptr)
        this->_move->play();
}

void Voice:: voiceEat()
{
    if(_eat!= nullptr)
        this->_eat->play();
}

void Voice:: voiceEnd()
{
    if(_end!= nullptr)
        this->_end->play();
}

void Voice:: voicejiangjun(){
    if(_jiangjun!= nullptr)
        this->_jiangjun->play();
}
