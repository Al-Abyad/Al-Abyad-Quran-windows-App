#include "qary.h"

Qary::Qary()
{

}

void Qary::setName(QString n)
{
    name=n;
}

void Qary::setDir(QString d)
{
    dir=d;
}




void Qary::setUrl(QString u)
{
    url=u;
}

void Qary::setType(QString t)
{
    type=t;
}

void Qary::setId(int i)
{
    id=i;
}

int Qary::getId()
{
    return id;
}

QString Qary::getName()
{
    return name;
}

QString Qary::getDir()
{
    return dir;
}

QString Qary::getUrl()
{
    return url;
}

QString Qary::getType()
{
    return type;
}

