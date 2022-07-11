#include "page.h"
#include <QDebug>

const int xPage=640;

Page::Page()
{

}

void Page::setNumber(const int n)
{
    number=n;
    image1=new QFile();
    image2=new QFile();
    if(n!=1){
        page1=number*2-1;
        page2=number*2;

    }
    else{

        page1=1;
        page2=2;
    }
    image1->setFileName(QString("img\\%1.png").arg(page1));
    image2->setFileName(QString("img\\%1.png").arg(page2));

    image1->open(QIODevice::ReadOnly);
    image2->open(QIODevice::ReadOnly);
    byte1=image1->readAll();
    byte2=image2->readAll();
//    byte1.loadFromData(image1->readAll());
//    byte2.loadFromData(image2->readAll());
    image1->close();
    image2->close();

}

void Page::setAyePages(QList<Aye *> ayePage1, QList<Aye *> ayePage2)
{
    this->ayePage1=ayePage1;
    this->ayePage2=ayePage2;
    createAllAyePage();


}

QList<Aye*> Page::getAyesPage()
{


    return allAyePage;
}

QList<Aye *> Page::getAyePage1()
{
    return ayePage1;
}

QList<Aye *> Page::getAyePage2()
{
    return ayePage2;
}

int Page::getNumber()const
{
    return number;
}

int Page::getNumPage1() const
{
    return page1;
}

int Page::getNumPage2() const
{
    return page2;
}

int Page::getNumAye() const
{
    return allAyePage.count();
}

int Page::getNumAyePage1()
{
    return ayePage1.count();
}
int Page::getNumAyePage2()
{
    return ayePage2.count();
}

QByteArray Page::getImage1()
{
    return byte1;//image1->readAll();
}

QByteArray Page::getImage2()
{
    return byte2;//image2->readAll();
}

void Page::createAllAyePage()
{
    int ayeInTwoPage=1;

    QList<AyeCordinate> cordinate;
    AyeCordinate cordinateTemp;
    Aye *tempAye;
    int line;
    for(int i=0;i<ayePage1.count();i++){
        tempAye=ayePage1.at(i);
        tempAye->setNumAyePageInTwoPage(ayeInTwoPage);
        cordinate=tempAye->getCordinate();
        line=tempAye->getNumLine();
        for(int j=0;j<line;j++){
            cordinateTemp=cordinate.at(j);
            cordinateTemp.setXb(cordinateTemp.getXb()+xPage);
            cordinate.replace(j,cordinateTemp);

            //فرضا یک خط اضافه میشه برای دایره ها
            if(line-1==j && cordinateTemp.getWidth()>50){
                tempAye->setNumLine(tempAye->getNumLine()+1);
                cordinateTemp.setLine(line+1);
                if(tempAye->getPage()==1)
                    cordinateTemp.setWidth(27);
                else
                    cordinateTemp.setWidth(42);

                cordinate.append(cordinateTemp);
            }


        }
        tempAye->setCordinate(cordinate);
//        ayePage1.replace(i,tempAye);

        ayeInTwoPage++;

    }


    for(int i=0;i<ayePage2.count();i++){
        tempAye=ayePage2.at(i);
        tempAye->setNumAyePageInTwoPage(ayeInTwoPage);
        cordinate=tempAye->getCordinate();
        cordinateTemp=cordinate.at(tempAye->getNumLine()-1);
        //فرضا یک خط اضافه میشه برای دایره ها
        if(cordinateTemp.getWidth()>50){
            tempAye->setNumLine(tempAye->getNumLine()+1);
            cordinateTemp.setLine(line+1);
            if(tempAye->getPage()==1)
                cordinateTemp.setWidth(27);
            else
                cordinateTemp.setWidth(42);

            cordinate.append(cordinateTemp);
        }
        tempAye->setCordinate(cordinate);

        ayeInTwoPage++;
    }
    allAyePage.append(ayePage1);
    allAyePage.append(ayePage2);
}

