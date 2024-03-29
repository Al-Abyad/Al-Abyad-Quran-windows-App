#include "customslider.h"




CustomSlider::CustomSlider(QWidget *parent):QSlider(parent)
{

}

void CustomSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (orientation() == Qt::Vertical)
            setValue(minimum() + ((maximum()-minimum()) * (height()-event->y())) / height() ) ;
        else
            setValue(minimum() + ((maximum()-minimum()) * event->x()) / width() ) ;


        event->accept();
    }
    QSlider::mousePressEvent(event);
    emit changedValue(value());
}
