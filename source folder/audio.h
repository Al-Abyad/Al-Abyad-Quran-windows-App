#ifndef AUDIO_H
#define AUDIO_H

#include <QMediaPlayer>
#include <QTimer>

class Audio:public QObject
{
    Q_OBJECT
public:
    Audio();
    void play();
    void pause();
    void stop();


    void setSoundPath(QString f);
    void setBackForwardMsc(int m);
    void backward();
    void forward();
    bool isPlay();
    bool isPause();
    bool isStop();

    int getPosition();
    int getVolum();

    int getDuration();

    void fadeSound();

    bool isFade();


public slots:
    void setPosition(int p);
    void setVolum(int v);
private:
    QMediaPlayer *mediaPlayer;
    QTimer *timer,*fadeTimer;
    int volum;
    int position;
    int mscBackForward;

    bool playState,pauseState,stopState;

    bool fadeOn;



private slots:
    void timerChange();
    void checkPlayerState(QMediaPlayer::MediaStatus s);
    void emitDuration(qint64 d);

    void checkFeadeTimer();
signals:
    void changePosition(int);
    void duration(int);
    void endSound();
    void paused();
    void stoped();
    void played();
    void volumChange(int);
    void fadeEnd();

};

#endif // AUDIO_H
