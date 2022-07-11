#include "sore.h"

Sore::Sore()
{

}

void Sore::setName(QString n)
{

    name=n;

}

void Sore::setVerse(int v)
{
    verse=v;
}

void Sore::setNumber(int n)
{

    number=n;
}

void Sore::setAye(QList<Aye *> a)
{

    aye=a;

    setSoreNameInAye();


}

void Sore::setLocNozol(QString l)
{
    loc_nozol=l;
}

void Sore::setTratibNozol(QString n)
{
    tartib_nozol=n;
}

void Sore::setEnName(QString n)
{
    en_name=n;
}

void Sore::setFazl(QString f)
{
    fazl=f;
}

void Sore::setBarekat(QString b)
{
    barekat=b;
}

void Sore::setTrans(QString t)
{
    transliteration=t;
}

QString Sore::getLocNozol()
{
    return loc_nozol;
}

QString Sore::getTartibNozol()
{
    return tartib_nozol;
}

QString Sore::getEnName()
{
    return en_name;
}

QString Sore::getFazl()
{
    return fazl;
}

QString Sore::getBarekat()
{
    return barekat;
}

QString Sore::getTrans()
{
    return transliteration;
}

QString Sore::getName()
{
    return name;
}

int Sore::getVerse()
{
    return verse;
}

int Sore::getNumber()
{
    return number;
}

QList<Aye *> Sore::getAye()
{
    return aye;
}

void Sore::setSoreNameInAye()
{


    for(int i=0;i<aye.count();i++)
        aye.at(i)->setSoreName(name);

}

