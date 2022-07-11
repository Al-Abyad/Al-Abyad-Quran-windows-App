#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QSlider>
#include <QWidget>
#include <QMouseEvent>

class CustomSlider: public QSlider
{

    Q_OBJECT

public:
    explicit CustomSlider(QWidget *parent);

protected:
  void mousePressEvent ( QMouseEvent * event );

signals:
  void changedValue(int);
};

#endif // CUSTOMSLIDER_H
