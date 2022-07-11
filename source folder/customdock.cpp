#include "customdock.h"

CustomDock::CustomDock(QWidget *parent) : QDockWidget(parent){

}

void CustomDock::closeEvent(QCloseEvent *event){

    emit close();
}


void CustomDock::setName(QString n){
    name=n;
}

