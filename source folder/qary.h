#ifndef QARY_H
#define QARY_H

#include <QString>
class Qary
{
public:
    Qary();
    void setName(QString n);
    void setDir(QString d);
    void setUrl(QString u);
    void setType(QString t);
    void setId(int i);

    int getId();
    QString getName();
    QString getDir();
    QString getUrl();
    QString getType();
private:
    QString name,dir,url,type;
    int id;

};

#endif // QARY_H
