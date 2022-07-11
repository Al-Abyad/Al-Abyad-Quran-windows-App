#ifndef ADDREAD_H
#define ADDREAD_H

#include <QDialog>
#include "language.h"

namespace Ui {
class AddRead;
}

class AddRead : public QDialog
{
    Q_OBJECT

public:
    explicit AddRead(QWidget *parent = 0);
    ~AddRead();

    void show();

    void setTextWidgets();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddRead *ui;

    void setComboItem();
    void setWidgets();


signals:
    void pageRead(int,int,int);
};

#endif // ADDREAD_H
