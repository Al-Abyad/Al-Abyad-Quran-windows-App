#include "scenepage.h"
#include <QFile>
#include <QByteArray>
#include <QImage>
ScenePage::ScenePage()
{
    currentPage=NULL;
    hiddenPage=false;
}

ScenePage::ScenePage(QObject *parent) : QGraphicsScene(parent)
{
    currentPage=NULL;
    hiddenPage=false;
}

ScenePage::~ScenePage()
{
    for(int i=0;i<items.count();i++){
        removeItem(items.at(i));
        delete items.at(i);

    }
    pixPage.clear();
}



void ScenePage::paintPage(Page *p,const int ayePage)
{


    currentPage=p;
    setPixmaps(p->getNumber());
    takePart();
    if(hiddenPage)
        paintHidden(ayePage);
    else
        paint(ayePage);
}



void ScenePage::nextPageHandle()
{
    emit nextPage();
}

void ScenePage::setHiddenPage(bool b)
{
    hiddenPage=b;
}

bool ScenePage::isHidden()
{
    return hiddenPage;
}



void ScenePage::setPixmapPage(QPixmap p)
{
    pix=p;
    this->addPixmap(pix);

}

void ScenePage::setPixmaps(int page)
{
    int p1,p2;
    if(page==1){
        p1=1;
        p2=2;
    }
    else {
        p1=page*2-1;
        p2=page*2;
    }


//    QFile file(QString("img\\%1.png").arg(p1));
//    QFile file2(QString("img\\%1.png").arg(p2));
//    file.open(QIODevice::ReadOnly);
//    QByteArray image = file.readAll();
//    file2.open(QIODevice::ReadOnly);
//    QByteArray image2 = file2.readAll();
//    QPixmap pix1;
//    pix1.loadFromData(image, 0, Qt::AutoColor);
//    QPixmap pix2;
//    pix2.loadFromData(image2 ,0, Qt::AutoColor);

    QPixmap pix1,pix2;
    pix1.loadFromData(currentPage->getImage1());
    pix2.loadFromData(currentPage->getImage2());


    QPixmap *pix=new QPixmap(pix1.width()+pix2.width(),pix1.height());

    QPainter *p=new QPainter(pix);
    p->drawPixmap(0,0,pix2.width(),pix2.height(),pix2);
    p->drawPixmap(pix2.width(),0,pix2.width(),pix2.height(),pix1);
    p->end();

    qDebug()<<"item count "<<pix->width()<<" "<<pix->height();
    setPixmapPage(*pix);

    delete pix;

}



void ScenePage::takePart()
{


    QPixmap p;
    items.clear();
    pixPage.clear();
    QList<Aye*> tempListAye=currentPage->getAyesPage();
    Aye *tempAye;
    QList<AyeCordinate> tempListCordinate;
    AyeCordinate tempCordinate;
    QList<QPixmap> tempListPix;
    int line;

    for(int i=0;i<tempListAye.count();i++){
        tempAye=tempListAye.at(i);
        tempListCordinate=tempAye->getCordinate();
        line=tempAye->getNumLine();

        for(int j=0;j<line;j++){
            tempCordinate=tempListCordinate.at(j);

            p=pix.copy(tempCordinate.getXb(),tempCordinate.getyb(),tempCordinate.getWidth(),tempCordinate.getHeight());

            items.append(new AyePixItem());
            items.last()->setPixmap(p);
            items.last()->setAyePage(tempAye->getAyePage());
            items.last()->setAyeInTwoPage(tempAye->getAyeInTwoPage());
            items.last()->setColor(tempAye->getColor());
            items.last()->setNumAyeSore(tempAye->getVerse());
            items.last()->setNumSore(tempAye->getChapter());
            items.last()->setPage(tempAye->getPage());
            items.last()->setLine(j+1);
            items.last()->setX(tempCordinate.getXb());
            items.last()->setY(tempCordinate.getyb());
            tempListPix.append(p);
            connect(items.last(),SIGNAL(ayeItamClicked(int,int)),this,
                    SLOT(itemClickHandle(int,int)));
            connect(items.last(),SIGNAL(contextClicked(int,int,QString)),this,
                    SLOT(contextMenuItemHandle(int,int,QString)));
        }
        pixPage.append(tempListPix);
        tempListPix.clear();
    }

}

void ScenePage::paint(int index)
{
    QImage img;
    unsigned int rgb;;
    for(int i=0;i<items.count();i++){
        if(items.at(i)->getAyeInTwoPage()==index){
            img=items.at(i)->pixmap().toImage();


            if(items.at(i)->pixmap().width()<50
                    && QString::compare(items.at(i)->getColor(),"blue")!=0
                    && items.at(i)->getNumAyeSore()!=0
                    && currentPage->getNumber()!=1
                    //&& currentPage->getAyesPage().at(items.at(i)->getNumAyePage()-1)->getNumLine()==items.at(i)->getLine()
            ){
                for(int y=0;y<img.height();y++){
                  for(int x=0;x<img.width();x++){
                      rgb=img.pixel(x,y);
                      if(qRed(rgb)!=255 && qGreen(rgb)!=252 && qBlue(rgb)!=217 && currentPage->getNumber()!=1){
                          if(QString::compare(items.at(i)->getColor(),"red")==0){
                              img.setPixel(x,y,qRgba(255,qGreen(rgb),qBlue(rgb),120));
                          }
                          else if(QString::compare(items.at(i)->getColor(),"yellow")==0){
                              img.setPixel(x,y,qRgba(255,255,qBlue(rgb),120));
                          }
                          else if(QString::compare(items.at(i)->getColor(),"green")==0){
                              img.setPixel(x,y,qRgba(qRed(rgb),255,qBlue(rgb),120));
                          }
                      }
                          //img.setPixel(x,y,qRgb(QColor(items.at(i)->getColor()).red(),QColor(items.at(i)->getColor()).green(),QColor(items.at(i)->getColor()).blue()));



                  }
                }
            }
            else{

                for(int y=0;y<img.height();y++){
                    for(int x=0;x<img.width();x++){
                      rgb=img.pixel(x,y);
                      if(currentPage->getNumber()!=1 && qRed(rgb)!=255 && qGreen(rgb)!=252 && qBlue(rgb)!=217)
                          img.setPixel(x,y,qRgba(qRed(rgb),qGreen(rgb),255,120));
                      else if(currentPage->getNumber()==1 && qRed(rgb)!=193 && qGreen(rgb)!=225 && qBlue(rgb)!=176)
                          img.setPixel(x,y,qRgba(qRed(rgb),qGreen(rgb),255,120));
                    }
                }
            }

            items.at(i)->setPixmap(QPixmap::fromImage(img));

            this->addItem(items.at(i));

        }
        else{

            if(items.at(i)->pixmap().width()<50
                    && QString::compare(items.at(i)->getColor(),"blue")!=0
                    && items.at(i)->getNumAyeSore()!=0
                    && currentPage->getNumber()!=1
                    //&& currentPage->getAyesPage().at(items.at(i)->getNumAyePage()-1)->getNumLine()==items.at(i)->getLine()
            ){
                img=items.at(i)->pixmap().toImage();
                for(int y=0;y<img.height();y++){
                  for(int x=0;x<img.width();x++){
                      rgb=img.pixel(x,y);
                      if(currentPage->getNumber()!=1 && qRed(rgb)!=255 && qGreen(rgb)!=252 && qBlue(rgb)!=217){
                          if(QString::compare(items.at(i)->getColor(),"red")==0){
                              img.setPixel(x,y,qRgba(255,qGreen(rgb),qBlue(rgb),120));
                          }
                          else if(QString::compare(items.at(i)->getColor(),"yellow")==0){
                              img.setPixel(x,y,qRgba(255,255,qBlue(rgb),120));
                          }
                          else if(QString::compare(items.at(i)->getColor(),"green")==0){
                              img.setPixel(x,y,qRgba(qRed(rgb),255,qBlue(rgb),120));
                          }
                      }


                  }
                }
                items.at(i)->setPixmap(QPixmap::fromImage(img));
                this->addItem(items.at(i));
            }
            else{

                this->addItem(items.at(i));
            }


        }
    }

}

void ScenePage::paintHidden(int index)
{
    QImage img;
    unsigned int rgb;;
    for(int i=0;i<items.count();i++){
        if(items.at(i)->getAyeInTwoPage()==index){
            img=items.at(i)->pixmap().toImage();


            if(items.at(i)->pixmap().width()<50 && items.at(i)->getNumAyeSore()!=0 ){// && currentPage->getAyesPage().at(items.at(i)->getNumAyePage()-1)->getNumLine()==items.at(i)->getLine()){
                for(int y=0;y<img.height();y++){
                  for(int x=0;x<img.width();x++){
                      rgb=img.pixel(x,y);
                      if(currentPage->getNumber()!=1 && qRed(rgb)!=255 && qGreen(rgb)!=252 && qBlue(rgb)!=217){
                          if(QString::compare(items.at(i)->getColor(),"red")==0){
                              img.setPixel(x,y,qRgba(255,qGreen(rgb),qBlue(rgb),120));
                          }
                          else if(QString::compare(items.at(i)->getColor(),"yellow")==0){
                              img.setPixel(x,y,qRgba(255,255,qBlue(rgb),120));
                          }
                          else if(QString::compare(items.at(i)->getColor(),"green")==0){
                              img.setPixel(x,y,qRgba(qRed(rgb),255,qBlue(rgb),120));
                          }
                          else
                              img.setPixel(x,y,qRgba(qRed(rgb),qGreen(rgb),255,120));
                      }

                      else if(currentPage->getNumber()==1 && qRed(rgb)!=193 && qGreen(rgb)!=225 && qBlue(rgb)!=176)
                          img.setPixel(x,y,qRgba(qRed(rgb),qGreen(rgb),255,120));

                  }
                }
            }
            else{

                for(int y=0;y<img.height();y++){
                    for(int x=0;x<img.width();x++){
                      rgb=img.pixel(x,y);
                      if(currentPage->getNumber()!=1 && qRed(rgb)!=255 && qGreen(rgb)!=252 && qBlue(rgb)!=217 )
                          img.fill(QColor(255,252,217));
                      else if(currentPage->getNumber()==1 && qRed(rgb)!=193 && qGreen(rgb)!=225 && qBlue(rgb)!=176)
                          img.fill(QColor(193,225,176));
                    }
                }
            }

            items.at(i)->setPixmap(QPixmap::fromImage(img));

            this->addItem(items.at(i));

        }
        else{

            if(items.at(i)->pixmap().width()<50 && items.at(i)->getNumAyeSore()!=0 ){// && currentPage->getAyesPage().at(items.at(i)->getNumAyePage()-1)->getNumLine()==items.at(i)->getLine()){

                this->addItem(items.at(i));
            }
            else{

                img=items.at(i)->pixmap().toImage();
                for(int y=0;y<img.height();y++){
                    for(int x=0;x<img.width();x++){
                      rgb=img.pixel(x,y);
                      if(currentPage->getNumber()!=1 && qRed(rgb)!=255 && qGreen(rgb)!=252 && qBlue(rgb)!=217)
                          img.fill(QColor(255,252,217));
                      else if(currentPage->getNumber()==1 && qRed(rgb)!=193 && qGreen(rgb)!=225 && qBlue(rgb)!=176)
                          img.fill(QColor(193,225,176));
                    }
                }


            items.at(i)->setPixmap(QPixmap::fromImage(img));

            this->addItem(items.at(i));
                //this->addItem(items.at(i));
            }


        }
    }
}

void ScenePage::itemClickHandle(int sore, int ayeSore)
{
    emit itemClicked(sore,ayeSore);
}

void ScenePage::contextMenuItemHandle(int sore, int aye, QString color)
{
    emit clickedContext(sore,aye,color);
}


void ScenePage::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mousePressEvent(event);
}
