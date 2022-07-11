#include "language.h"

QString Language::currentLanguage="";
QList<QString> Language::languages;
QMap<QString,QString> Language::dictionary;
QMap<QString,QString> Language::deDictionary;
Language::Language()
{

}

void Language::loadLanguages()
{
    QDir dir("/language");
    if(!dir.exists())
        QDir().mkdir("language");
    QDir langDir(":/rec/lang/");
    QFileInfoList files=langDir.entryInfoList();

    QFile lang;

    for(int i=0;i<files.count();i++){
        lang.setFileName(files.at(i).absoluteFilePath());

        languages.append(files.at(i).baseName());
        if(!QFile().exists(QString("language//%1.xml").arg(files.at(i).baseName())))
            lang.copy(QString("language//%1.xml").arg(files.at(i).baseName()));
    }

        setDictionary();


}

void Language::setCurrentLanguage(QString l)
{
    currentLanguage=l;

    setDictionary();
}

Qt::LayoutDirection Language::getDirection()
{
    if(QString::compare(dictionary.value("Align"),"Right")==0)
        return Qt::RightToLeft;
    else
        return Qt::LeftToRight;
}

Global::KeyBoardLang Language::getKeyBoardLanguage()
{
    char langKey [KL_NAMELENGTH];
    GetKeyboardLayoutNameA (langKey);

    if((langKey[5]*100+langKey[6]*10+langKey[7])==5757)  //persian
        return Global::Persian;

    else if(langKey[5]*100+langKey[6]*10+langKey[7]==5729)   //arabic 101
        return Global::Arabic;
}

QString Language::getCurrentLanguage()
{
    return currentLanguage;
}

QList<QString> Language::getLanguges()
{
    return languages;
}

QString Language::translate(QString key)
{
    return dictionary.value(key);
}

QString Language::deTranslate(QString value)
{
    return deDictionary.value(value);
}

void Language::setDictionary()
{
    if(QString::compare(currentLanguage,"")!=0){
        dictionary.clear();
        deDictionary.clear();
        QDomDocument d;
        QDomNodeList nodeList;
        QFile file(QString("language/%1.xml").arg(currentLanguage));
        file.open(QIODevice::ReadOnly);

        d.setContent(&file);
        file.close();
        nodeList=d.elementsByTagName("text");
        QDomElement elemnt;

        for(int i=0;i<nodeList.count();i++){
            elemnt=nodeList.at(i).toElement();
            dictionary.insert(elemnt.attributeNode("id").value(),elemnt.attributeNode("value").value());
            deDictionary.insert(elemnt.attributeNode("value").value(),elemnt.attributeNode("id").value());
        }
    }


}

