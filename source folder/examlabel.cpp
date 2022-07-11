#include "examlabel.h"
#include <QDebug>
ExamLabel::ExamLabel(QWidget *parent):QLabel(parent)
{

}


void ExamLabel::mousePressEvent(QMouseEvent *ev){
//    if(ev->flags()==Qt::MouseEventCreatedDoubleClick)
        emit clicked();

    qDebug()<<"exam click";
}
