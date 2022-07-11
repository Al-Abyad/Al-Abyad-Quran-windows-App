#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QSplashScreen>
#include "mainwindow.h"
#include <setting.h>
#include <QNetworkReply>
#include <QTextCodec>
#include <QNetworkInterface>
#include <QDate>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);

    ~Register();

private slots:
    void on_pushButton_send_mobile_clicked();
    void netcheck(QNetworkReply *r);
    void on_pushButton_check_code_clicked();
    void errorNetwork(QNetworkReply::NetworkError err);

    void on_radioButton_mob_toggled(bool checked);

    void on_pushButton_send_email_clicked();

private:
    Ui::Register *ui;
    QSplashScreen *splash;
    MainWindow *w;
    Setting *setting;
    QNetworkAccessManager *network;

    QNetworkReply *rep;
    QString code;

    QString mobOrEmail;


    void returnCount();



};

#endif // REGISTER_H
