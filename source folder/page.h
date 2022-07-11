#ifndef PAGE_H
#define PAGE_H

#include "aye.h"
#include "ayecordinate.h"
#include <QPixmap>
#include <QFile>
class Page
{
public:
    Page();
    void setNumber(int n);
    void setPages(int page1,int page2);
    void setAyePages(QList<Aye*> ayePage1,QList<Aye*> ayePage2);

    QList<Aye*> getAyesPage();
    QList<Aye*> getAyePage1();
    QList<Aye*> getAyePage2();
    int getNumber() const;
    int getNumPage1() const;
    int getNumPage2() const;
    int getNumAye() const;
    int getNumAyePage1();
    int getNumAyePage2();
    QByteArray getImage1();
    QByteArray getImage2();





private:
    int number;
    int page1,page2;
    int numAyePage1,numAyePage2;
    QList<Aye*> allAyePage;
    QList<Aye*> ayePage1,ayePage2;
    QFile *image1;
    QFile *image2;
    QByteArray byte1,byte2;
    void createAllAyePage();


};

#endif // PAGE_H
