#include "translation.h"

Translation::Translation()
{

}

Translation::Translation(QString lang, QString trans)
{
    language=lang;
    translator=trans;
}

void Translation::setLanguage(QString l)
{
    language=l;
}

void Translation::setName(QString n)
{
    name=n;
}

void Translation::setTranslator(QString t)
{
    translator=t;
}

QString Translation::getLanguage()
{
    return language;
}

QString Translation::getName()
{
    return name;
}

QString Translation::getTranslator()
{
    return translator;
}

