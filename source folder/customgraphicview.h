#ifndef CUSTOMGRAPHICVIEW_H
#define CUSTOMGRAPHICVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QMouseEvent>

class CustomGraphicView:public QGraphicsView
{
public:
    explicit CustomGraphicView(QWidget *parent);
protected:
    void mousePressEvent(QMouseEvent *event);


};

#endif // CUSTOMGRAPHICVIEW_H
