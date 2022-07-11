#ifndef SORE_H
#define SORE_H

#include <QString>
#include "aye.h"
#include <QList>

#include <QDebug>
class Sore
{
public:
    Sore();

    void setName(QString n);
    void setVerse(int v);
    void setNumber(int n);
    void setAye(QList<Aye*> a);
    void setLocNozol(QString l);//location
    void setTratibNozol(QString n);
    void setEnName(QString n);
    void setFazl(QString f);
    void setBarekat(QString b);
    void setTrans(QString t);//transliteration

    QString getLocNozol();
    QString getTartibNozol();
    QString getEnName();
    QString getFazl();
    QString getBarekat();
    QString getTrans();
    QString getName();
    int getVerse();
    int getNumber();
    QList<Aye*> getAye();

private:
    QString name;
    int verse;
    int number;
    QString loc_nozol,tartib_nozol;
    QString en_name;
    QString fazl;
    QString barekat;
    QString transliteration;
    QList<Aye*> aye;

    void setSoreNameInAye();
};

#endif // Sore_H
