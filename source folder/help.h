#ifndef HELP_H
#define HELP_H

#include <QDialog>
#include <QDesktopServices>
#include "language.h"
#include <QUrl>

namespace Ui {
class Help;
}

class Help : public QDialog
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = 0);
    ~Help();


    void setWidgetText();

private slots:


    void on_pushButton_contact_clicked();

    void on_pushButton_guide_clicked();

    void on_pushButton_site_clicked();

private:
    Ui::Help *ui;

    QUrl contact,guide,site;
};

#endif // HELP_H
