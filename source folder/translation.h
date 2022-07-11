#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QString>
class Translation
{
public:
    Translation();
    Translation(QString lang,QString trans);
    void setLanguage(QString l);
    void setName(QString n);
    void setTranslator(QString t);

    QString getLanguage();
    QString getName();
    QString getTranslator();
private:
   QString language;
   QString name;
   QString translator;

};


#endif // TRANSLATION_H
