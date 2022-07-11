#ifndef EXAMLABEL_H
#define EXAMLABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
class ExamLabel:public QLabel
{
    Q_OBJECT
public:
    explicit ExamLabel(QWidget *parent);
    void mousePressEvent(QMouseEvent *ev);

signals:
    void clicked();
};

#endif // EXAMLABEL_H
