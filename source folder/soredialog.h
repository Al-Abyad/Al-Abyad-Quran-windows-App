#ifndef SOREDIALOG_H
#define SOREDIALOG_H

#include <QDialog>
#include "sore.h"

#include <QTableWidgetItem>
#include <QTableWidget>
#include "language.h"
namespace Ui {
class SoreDialog;
}

class SoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SoreDialog(QWidget *parent = 0);
    ~SoreDialog();

    Q_INVOKABLE void setSore(Sore *s);

    void setWidgetText();

private:
    Ui::SoreDialog *ui;

    Sore *currentSore;

    void showTable();
};

#endif // SOREDIALOG_H
