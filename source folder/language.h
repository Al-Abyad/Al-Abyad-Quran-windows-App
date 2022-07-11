#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QString>
#include <windows.h>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDomDocument>
#include <QDomNodeList>
#include <QDomElement>
#include <QDebug>
#include "global.h"
class Language
{
public:
    Language();

    static void loadLanguages();
    static void setCurrentLanguage(QString l);
    static Qt::LayoutDirection getDirection();
    static Global::KeyBoardLang getKeyBoardLanguage();
    static QString getCurrentLanguage();
    static QList<QString> getLanguges();
    static QString translate(QString key);
    static QString deTranslate(QString value);

private:
    static QString currentLanguage;
    static QList<QString> languages;
    static QMap<QString,QString> dictionary;
    static QMap<QString,QString> deDictionary;
    static void setDictionary();


};

#endif // LANGUAGE_H
