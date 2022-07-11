#include "audio.h"

Audio::Audio()
{
    mediaPlayer=new QMediaPlayer(this);
    timer=new QTimer(this);
    fadeTimer=NULL;
    position=0;
    mscBackForward=3000;

    volum=100;
    mediaPlayer->setVolume(volum);
    playState=false;
    pauseState=false;
    stopState=true;

    connect(timer,SIGNAL(timeout()),this,SLOT(timerChange()));
    connect(mediaPlayer,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this,SLOT(checkPlayerState(QMediaPlayer::MediaStatus)));
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(emitDuration(qint64)));
}

void Audio::play()
{
    mediaPlayer->play();
    timer->start(1);
    playState=true;
    pauseState=false;
    stopState=false;

    emit played();
}

void Audio::pause()
{
    mediaPlayer->pause();
    timer->stop();
    playState=false;
    pauseState=true;
    stopState=false;

    emit paused();
}
void Audio::stop()
{
    mediaPlayer->stop();
    timer->stop();
    playState=false;
    pauseState=false;
    stopState=true;
    position=0;

    emit changePosition(0);
    emit stoped();
}

void Audio::setPosition(int p)
{
    mediaPlayer->setPosition(p);
    position=p;

}

void Audio::setVolum(int v)
{
    mediaPlayer->setVolume(v);
    volum=v;
    emit volumChange(mediaPlayer->volume());
}

void Audio::setSoundPath(QString f)
{
    mediaPlayer->setMedia(QUrl::fromLocalFile(f));
}

void Audio::setBackForwardMsc(int m)
{
    mscBackForward=m;
}

void Audio::backward()
{
    int p=mediaPlayer->position()-mscBackForward;
    mediaPlayer->setPosition(p);
    position=p;
    emit changePosition(p);

}

void Audio::forward()
{
    int p=mediaPlayer->position()+mscBackForward;
    mediaPlayer->setPosition(p);
    position=p;
    emit changePosition(p);
}

bool Audio::isPlay()
{
    return playState;
}

bool Audio::isPause()
{
    return pauseState;
}

bool Audio::isStop()
{
    return stopState;
}

int Audio::getPosition()
{
    return mediaPlayer->position();

}

int Audio::getVolum()
{
    return mediaPlayer->volume();
}

int Audio::getDuration()
{
    return mediaPlayer->duration();
}

void Audio::fadeSound()
{
    qDebug()<<"fade start!";
    if(fadeTimer==NULL){
        fadeTimer=new QTimer;
        connect(fadeTimer,SIGNAL(timeout()),this,SLOT(checkFeadeTimer()));
    }
    fadeOn=true;

    fadeTimer->start(5);
}

bool Audio::isFade()
{
    return fadeOn;
}

void Audio::checkFeadeTimer()
{

    qDebug()<<"fade timer ";
    if(mediaPlayer->volume()!=0)
        mediaPlayer->setVolume(mediaPlayer->volume()-1);
    else{

        fadeTimer->stop();
        fadeOn=false;
        mediaPlayer->stop();
        mediaPlayer->setVolume(volum);
        emit fadeEnd();
    }
}

void Audio::timerChange()
{
    position++;

    emit changePosition(position);
}

void Audio::checkPlayerState(QMediaPlayer::MediaStatus s)
{
    if(s==QMediaPlayer::EndOfMedia){
        timer->stop();
        position=0;
        emit endSound();
    }
}

void Audio::emitDuration(qint64 d)
{
    emit duration(d);
}




