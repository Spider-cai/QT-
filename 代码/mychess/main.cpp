#include<QApplication>
#include"Board.h"
#include<QMessageBox>
#include<QObject>
#include"NetGame.h"
#include"Voice.h"
#include"Begin.h"
#include"Chosse_oneortwo.h"
#include"GameMidia.h"
int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    GameMidia *media=new GameMidia(":/new/prefix1/voice/backvoice.mp3");
    media->ForeverPlay();
    Begin *dlg=new Begin();
    dlg->show();

    return app.exec();

}
/*
Board *a=new Board();
if(dlg->exec() != QDialog::Accepted)
    return 0;
if(dlg->s==1) {
    dlg->hide();
    a->show();
}else
if(dlg->s==2){
    dlg->hide();
    setbuf(stdout, NULL);
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(NULL,"red or black","是否执红");
    bool e=false;
    if(ret==QMessageBox::Yes){
        e=true;
    }
    NetGame *c=new NetGame(e);
    c->show();
}else{
    if(dlg->s==3) return app.exec();
}*/




/*
    setbuf(stdout, NULL);
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(NULL,"red or black","是否执红");
    bool e=false;
    if(ret==QMessageBox::Yes){
        e=true;
    }
    */

/*


*/
/*
Voice i;
//i.voiceEat();
//i.voiceWin();
//i.voiceMove();
//i.voiceSelect();
i.voicejiangjun();
*/
