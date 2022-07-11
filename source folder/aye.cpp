#include "aye.h"
#include <QDebug>



Aye::Aye(){
    readDate=0;
    readCount=0;
}

void Aye::setText(QString v)
{
    text=v;

}

void Aye::setAudio(QString v)
{
    audio=v;
}

void Aye::setColor(QString v)
{
    color=v;
}

void Aye::setCordinate(QList<AyeCordinate> v)
{
    cordinate=v;
}

void Aye::setChapter(int v)
{
    Chapter=v;
}

void Aye::setVerse(int v)
{
    verse=v;
}

void Aye::setAyeQuran(int v)
{
    ayeQuran=v;
}

void Aye::setJuz(int v)
{
    juz=v;
}

void Aye::setPage(int v)
{
    page=v;
}

void Aye::setNumLine(int v){
    numLine=v;
}

void Aye::setAyePage(int v)
{
    ayePage=v;
}

void Aye::setNumAyePageInTwoPage(int v)
{
    numAyeInTwoPage=v;
}

void Aye::setSoreName(QString n)
{

    soreName=n;
}

void Aye::setReadDate(qint64 rd)
{
    readDate=rd;
    readCount++;
}

void Aye::setReadCount(int c)
{
    readCount=c;
}

QString Aye::getSoreName()
{
    return soreName;
}



int Aye::getAyePage()
{
    return ayePage;
}

int Aye::getAyeInTwoPage()
{
    return numAyeInTwoPage;
}

int Aye::getPage()
{
    return page;

}

int Aye::getChapter()
{
    return Chapter;

}

int Aye::getAyeQuran()
{
    return ayeQuran;
}

int Aye::getJuz()
{

    return juz;
}

int Aye::getNumLine()
{
    return numLine;
}

int Aye::getVerse()
{
    return verse;
}


QString Aye::getColor()
{
    return color;
}

QString Aye::getAudio()
{
    return audio;
}

QList<AyeCordinate> Aye::getCordinate()
{
if(page==187)
    qDebug()<<cordinate.count();

    return cordinate;
}

QString Aye::getText()
{
    return text;
}

qint64 Aye::getReadDate()
{
    return readDate;
}

int Aye::getReadCount()
{
    return readCount;
}
