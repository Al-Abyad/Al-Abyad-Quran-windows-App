#ifndef CUSTOMDOCK_H
#define CUSTOMDOCK_H

#include <QDockWidget>
class CustomDock : public QDockWidget{
    Q_OBJECT

public:
    explicit CustomDock(QWidget *parent = 0);
    void setName(QString n);

private:
    QString name;

protected:
    void closeEvent(QCloseEvent *event);




signals:
    void close();


};

#endif // CUSTOMDOCK_H
