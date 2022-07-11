#ifndef AYE_H
#define AYE_H

#include <QString>
#include <QList>
#include "ayecordinate.h"


class Aye
{
public:
    Aye();
    void setText(QString v);
    void setAudio(QString v);
    void setColor(QString v);
    void setCordinate(QList<AyeCordinate> v);
    void setChapter(int v);
    void setVerse(int v);
    void setAyeQuran(int v);
    void setJuz(int v);
    void setPage(int v);
    void setNumLine(int v);
    void setAyePage(int v);
    void setNumAyePageInTwoPage(int v);
    void setSoreName(QString n);

    void setReadDate(qint64 rd);
    void setReadCount(int c);


    QString getSoreName();
    int getAyePage();
    int getAyeInTwoPage();
    int getPage();
    int getNumLine();
    int getVerse();
    int getChapter();
    int getAyeQuran();
    int getJuz();
    QString getColor();
    QString getAudio();
    QList<AyeCordinate> getCordinate();
    QString getText();

    qint64 getReadDate();
    int getReadCount();
private:

    QString text;
    QString audio;
    QString color;
    QString soreName;
    int Chapter;
    int verse;
    int ayeQuran;
    int juz;
    int page;
    int numLine;
    int ayePage;
    int numAyeInTwoPage;
    qint64 readDate;
    int readCount;
    QList<AyeCordinate> cordinate;









};

#endif // AYE_H
