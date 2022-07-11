#include "ayepixitem.h"

#include <QApplication>
AyePixItem::AyePixItem(QGraphicsItem *parent):QObject(),QGraphicsPixmapItem(parent){


}

AyePixItem::AyePixItem()
{

}

void AyePixItem::setNumSore(const int s)
{
    numSore=s;
}

void AyePixItem::setNumAyeSore(const int s)
{
    numAyeSore=s;
}

void AyePixItem::setAyePage(const int p)
{
    numAyePage=p;
}

void AyePixItem::setAyeInTwoPage(int p)
{
    ayeInTwoPage=p;
}

void AyePixItem::setPage(const int p)
{
    numPage=p;
}

void AyePixItem::setColor(const QString c)
{
    color=c;
}

void AyePixItem::setLine(int l)
{
    line=l;
}

int AyePixItem::getNumSore()
{
    return numSore;
}

int AyePixItem::getNumAyeSore()
{
    return numAyeSore;
}

int AyePixItem::getNumAyePage()
{
    return numAyePage;
}

int AyePixItem::getAyeInTwoPage()
{
    return ayeInTwoPage;
}

int AyePixItem::getPage()
{
    return numPage;
}

int AyePixItem::getLine()
{
    return line;
}

QString AyePixItem::getColor()
{
    return color;
}



void AyePixItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if(event->button()==Qt::LeftButton)
        emit ayeItamClicked(numSore,numAyeSore);

}



void AyePixItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){

    QMenu *menu=new QMenu();

    menu->addAction(QIcon(":/rec/icon/014_060_add_product_crate_package_box_parcel_shipping_bundle_cargo.png"),Language::translate("read"));
    menu->addAction(QIcon(":/rec/icon/022_025_layers_front_copy_clone.png"),Language::translate("copy"));
    menu->addAction(QIcon(":/rec/green.png"),Language::translate("green"));
    menu->addAction(QIcon(":/rec/yellow.png"),Language::translate("yellow"));
    menu->addAction(QIcon(":/rec/red.png"),Language::translate("red"));
    menu->addAction(QIcon(":/rec/icon/024_141_cancel_stop_cancellation_forbidden.png"),Language::translate("delete"));
    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(contextMenuHandle(QAction*)));

    menu->exec(event->screenPos());

}

void AyePixItem::contextMenuHandle(QAction *a)
{
    emit contextClicked(numSore,numAyeSore,Language::deTranslate(a->text()));
}



void AyePixItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){



}

void AyePixItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){


}
