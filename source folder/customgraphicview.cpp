#include "customgraphicview.h"
#include <QDebug>
CustomGraphicView::CustomGraphicView(QWidget *parent):QGraphicsView(parent)
{

}


void CustomGraphicView::mousePressEvent(QMouseEvent *event)
{

    QGraphicsView::mousePressEvent(event);
}
