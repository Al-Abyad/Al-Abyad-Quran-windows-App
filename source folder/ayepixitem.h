#ifndef AYEPIXITEM_H
#define AYEPIXITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include "language.h"
#include <QDebug>
class  AyePixItem : public QObject,public QGraphicsPixmapItem
{

    Q_OBJECT

public:
   explicit AyePixItem(QGraphicsItem *parent);
    AyePixItem();
    void setNumSore(int s);
    void setNumAyeSore(int s);
    void setAyePage(int p);
    void setAyeInTwoPage(int p);
    void setPage(int p);
    void setColor(QString c);
    void setLine(int l);

    int getNumSore();
    int getNumAyeSore();
    int getNumAyePage();
    int getAyeInTwoPage();
    int getPage();
    int getLine();
    QString getColor();

private:
     QString color;
     int numSore;
     int numAyeSore;
     int numAyePage;
     int ayeInTwoPage;
     int numPage;
     int line;



protected:
         void mousePressEvent(QGraphicsSceneMouseEvent *event);
         void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
         void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
         void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);


private slots:
         void contextMenuHandle(QAction *a);

signals:
     void ayeItamClicked(int,int);
     void contextClicked(int,int,QString);


};

#endif // AYEPIXITEM_H
