#include <QApplication>

#include "register.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setLayoutDirection(Qt::RightToLeft);

    Register r;

//MainWindow w;
//w.show();


    return a.exec();
}
