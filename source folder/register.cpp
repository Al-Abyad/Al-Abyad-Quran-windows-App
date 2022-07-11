#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    QCoreApplication::setApplicationName("Abyaz");
    QCoreApplication::setOrganizationName("Abyaz-co");
    qApp->setWindowIcon(QIcon(":/rec/app.ico"));

    setting=new Setting(this);
//    QLibrary myLib("CIMWin32");
//    typedef void (*MyPrototype)();
//    MyPrototype myFunction = (MyPrototype) myLib.resolve("Win32_BaseBoard");
//    if (myFunction)
//        myFunction();

    //setting->saveSetting("register",0);
    QSettings s("microsoft","microsoft");
//    if(setting->loadSetting("register").toInt()==1 && s.value("key").toString().compare(setting->loadSetting("key").toString())==0){
        QPixmap pixmap(":/rec/alabyad-splash.png");
        splash = new QSplashScreen(pixmap);
        splash->show();

         // Loading some items
  //      splash->showMessage("Loaded modules");

        qApp->processEvents();

        w=new MainWindow;



        w->show();
        delete splash;
//    }
//    else{

//        this->show();
//    }


}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_send_mobile_clicked()
{

    if(!ui->lineEdit_mobile->text().isEmpty()){

        QByteArray postData;

        ui->pushButton_send_mobile->setEnabled(false);
        ui->radioButton_mail->setEnabled(false);

        //postData.append("mobile="+ui->lineEdit_mobile->text());
        ui->label_message->setText("Please Wait...");
        network=new QNetworkAccessManager(this);
        QNetworkRequest request;
        mobOrEmail=ui->lineEdit_mobile->text();
        request=QNetworkRequest(QUrl("http://al-abyad.ir/abyad/sms.php?mob="+ui->lineEdit_mobile->text()));
        rep=network->get(request);//,postData);

        connect(network,SIGNAL(finished(QNetworkReply*)),this,SLOT(netcheck(QNetworkReply*)));
        connect(rep, SIGNAL(error(QNetworkReply::NetworkError)),
                this,  SLOT(errorNetwork(QNetworkReply::NetworkError)));
    }
}

void Register::netcheck(QNetworkReply* r)
{
    if(r->error()==QNetworkReply::NoError){
        QByteArray b=r->readAll();

        if(QString(b).toInt()!=1){
            ui->lineEdit_code->setEnabled(true);
            ui->pushButton_check_code->setEnabled(true);
            code=QString(b);
            //ui->label_message->setText(QString(b));
            ui->label_message->setText("");


        }
        else{
            ui->label_message->setText(QString(b));
            ui->label_message->setText("The mobile or e-mail is not registered.");
            ui->pushButton_send_email->setEnabled(true);
            ui->pushButton_send_mobile->setEnabled(true);
            ui->radioButton_mob->setEnabled(true);
            ui->radioButton_mail->setEnabled(true);
        }
    }

    else{
        qDebug()<<"network Error "<<r->errorString();
        ui->label_message->setText("Internet Connection problem!");

        ui->pushButton_send_email->setEnabled(true);
        ui->pushButton_send_mobile->setEnabled(true);
        ui->radioButton_mob->setEnabled(true);
        ui->radioButton_mail->setEnabled(true);
    }


}



void Register::on_pushButton_check_code_clicked()
{
    if(ui->lineEdit_code->text().compare("")!=0){
        if(code.toInt()==ui->lineEdit_code->text().toInt()){
             this->close();
            setting->saveSetting("register",1);
            QPixmap pixmap(":/rec/alabyad-splash.png");
            splash = new QSplashScreen(pixmap);
            splash->show();

             // Loading some items
      //      splash->showMessage("Loaded modules");

            qApp->processEvents();

            w=new MainWindow;

            w->show();

            returnCount();

            setting->saveSetting("defaultMainWindow",w->saveState());
            setting->saveSetting("defaultCentralWindow",w->getCentralWindow()->saveState());


            setting->saveSetting("register",1);
            setting->saveSetting("appdate",QDate::currentDate().toJulianDay());
            QTextCodec *codec=QTextCodec::codecForName("Windows-1251");

            QString hash=QString(QCryptographicHash::hash(QCryptographicHash::hash(QByteArray(codec->fromUnicode(code)),QCryptographicHash::Md5),QCryptographicHash::Sha256));
            setting->saveSetting("key",hash);
            QSettings s("microsoft","microsoft");
            s.setValue("key",hash);

            delete splash;
        }
        else{
            ui->label_message->setText("The code is invalid!");
        }
    }
}

void Register::errorNetwork(QNetworkReply::NetworkError err)
{
    if(err !=QNetworkReply::NoError)
    {
        ui->label_message->setText("Internet Connection problem!");

        ui->pushButton_send_email->setEnabled(true);
        ui->pushButton_send_mobile->setEnabled(true);
        ui->radioButton_mob->setEnabled(true);
        ui->radioButton_mail->setEnabled(true);
    }
}


void Register::on_radioButton_mob_toggled(bool checked)
{
    if(checked){
        ui->pushButton_send_mobile->setEnabled(true);
        ui->lineEdit_mobile->setEnabled(true);

        ui->pushButton_send_email->setEnabled(false);
        ui->lineEdit_mail->setEnabled(false);
    }
    else{
        ui->pushButton_send_mobile->setEnabled(false);
        ui->lineEdit_mobile->setEnabled(false);

        ui->pushButton_send_email->setEnabled(true);
        ui->lineEdit_mail->setEnabled(true);
    }
}

void Register::on_pushButton_send_email_clicked()
{
    if(!ui->lineEdit_mail->text().isEmpty()){

        QByteArray postData;
        ui->pushButton_send_email->setEnabled(false);
        ui->radioButton_mob->setEnabled(false);
        //postData.append("mobile="+ui->lineEdit_mobile->text());
        ui->label_message->setText("Please Wait...");
        network=new QNetworkAccessManager(this);
        QNetworkRequest request;
        mobOrEmail=ui->lineEdit_mail->text();
        request=QNetworkRequest(QUrl("http://al-abyad.ir/abyad/email.php?email="+ui->lineEdit_mail->text()));
        rep=network->get(request);//,postData);

        connect(network,SIGNAL(finished(QNetworkReply*)),this,SLOT(netcheck(QNetworkReply*)));
        connect(rep, SIGNAL(error(QNetworkReply::NetworkError)),
                this,  SLOT(errorNetwork(QNetworkReply::NetworkError)));
    }
}

void Register::returnCount()
{
    QByteArray postData;

    network=new QNetworkAccessManager(this);
    QNetworkRequest request;
    if(ui->radioButton_mail->isChecked())
        request=QNetworkRequest(QUrl("http://al-abyad.ir/abyad/count.php?email="+mobOrEmail));
    else
        request=QNetworkRequest(QUrl("http://al-abyad.ir/abyad/count.php?mob="+mobOrEmail));
    rep=network->get(request);//,postData);
}
