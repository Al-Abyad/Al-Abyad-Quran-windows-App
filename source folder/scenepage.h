#ifndef SCENEPAGE_H
#define SCENEPAGE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "page.h"
#include "ayepixitem.h"

class ScenePage:public  QGraphicsScene{


    Q_OBJECT

    public:
        ScenePage();
        ScenePage(QObject *parent);
        ~ScenePage();

    void paintPage(Page *p, int ayePage);
    void nextPageHandle();
    void setHiddenPage(bool b);
    bool isHidden();



private:
    bool hiddenPage;
    QList<AyePixItem*> items;
    QList<QList<QPixmap> > pixPage;
    Page *currentPage;
    QPixmap pix;
    void setPixmaps(int page);
    void setPixmapPage(QPixmap p);
    void takePart();
    void paint(int index);
    void paintHidden(int index);

private slots:
    void itemClickHandle(int sore, int ayeSore);
    void contextMenuItemHandle(int sore,int aye,QString color);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void nextPage();
    void pereviousPage();
    void nextAye();
    void previousAye();
    void itemClicked(int,int);
    void clickedContext(int,int,QString);


};

#endif // SCENEPAGE_H
