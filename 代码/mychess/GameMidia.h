//GameMidia.h
#ifndef GAMEMIDIA_H
#define GAMEMIDIA_H

#include <QObject>
#include<QtMultimedia/QtMultimedia>
#include<QtMultimediaWidgets/QVideoWidget>
#include<QTimer>
class GameMidia : public QObject
{
    Q_OBJECT
public:
    explicit GameMidia(QString address,QObject *parent = nullptr);
    void ForeverPlay();
private:
    QMediaPlayer* media;
    QString path;
signals:

};

#endif // GAMEMIDIA_H
