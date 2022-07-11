#include "downloadcontrol.h"
#include "ui_downloadcontrol.h"

DownloadControl::DownloadControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadControl)
{
    ui->setupUi(this);

    count=0;

}

DownloadControl::~DownloadControl()
{
    delete ui;
}

void DownloadControl::setDownloadList(QQueue<DownloadInfo *> *list)
{
    downloadList=*list;

    ui->listWidget->clear();


    for(int i=0;i<list->count();i++)
        ui->listWidget->addItem(list->at(i)->getSavePath());

    if(list->count()>count)
        count=list->count();
    if(count>0)
        ui->progressBar->setValue(100-((list->count()*100)/count));
    if(list->isEmpty()){
        ui->progressBar->setValue(0);
        ui->label_current->setText("");
    }

}

void DownloadControl::setTextWidgets()
{
    this->setWindowTitle(Language::translate("download"));

    ui->pushButton->setText(Language::translate("stop"));

}

void DownloadControl::reciveCurrentDownload(qint64 bytesReceived, qint64 bytesTotal)
{

    if(!downloadList.isEmpty()){
        if(bytesTotal<1000){
            ui->label_current->setText(downloadList.at(0)->getSavePath()+":  "+QString("%1Byte/%2Byte").arg(bytesReceived,bytesTotal));
            //qDebug()<<downloadList.at(0)->getSavePath()+":  "+QString("%1Byte").arg(bytesReceived)+QString("/%1KB").arg(bytesTotal);

        }
        else if(bytesTotal>=1000 && bytesTotal<1000000){
            if(bytesReceived<1000){
                ui->label_current->setText(downloadList.at(0)->getSavePath()+":  "+QString("%1Byte").arg(bytesReceived)+QString("/%1KB").arg(bytesTotal/1000));
               // qDebug()<<downloadList.at(0)->getSavePath()+":  "+QString("%1Byte").arg(bytesReceived)+QString("/%1KB").arg(bytesTotal/1000);
            }
            else if(bytesReceived>=1000){
                ui->label_current->setText(downloadList.at(0)->getSavePath()+":  "+QString("%1KB").arg(bytesReceived/1000)+QString("/%1KB").arg(bytesTotal/1000));
                //qDebug()<<downloadList.at(0)->getSavePath()+":  "+QString("%1KB").arg(bytesReceived/1000)+QString("/%1KB").arg(bytesTotal/1000);
            }
        }
        else if(bytesTotal>=1000000){
            if(bytesReceived<1000){
                ui->label_current->setText(downloadList.at(0)->getSavePath()+":  "+QString("%1Byte").arg(bytesReceived)+QString("/%1MB").arg(bytesTotal/1000000));
                //qDebug()<<downloadList.at(0)->getSavePath()+":  "+QString("%1Byte").arg(bytesReceived)+QString("/%1MB").arg(bytesTotal/1000000);
            }
            else if(bytesReceived>=1000 && bytesReceived<1000000){
                ui->label_current->setText(downloadList.at(0)->getSavePath()+":  "+QString("%1KB").arg(bytesReceived/1000)+QString("/%1MB").arg(bytesTotal/1000000));
                //qDebug()<<downloadList.at(0)->getSavePath()+":  "+QString("%1KB").arg(bytesReceived/1000)+QString("/%1MB").arg(bytesTotal/1000000);
            }

            else if(bytesReceived>=1000000){
                ui->label_current->setText(downloadList.at(0)->getSavePath()+":  "+QString("%1MB").arg(bytesReceived/1000000)+QString("/%1MB").arg(bytesTotal/1000000));
                //qDebug()<<downloadList.at(0)->getSavePath()+":  "+QString("%1MB").arg(bytesReceived/1000000)+QString("/%1KB").arg(bytesTotal/1000000);
            }
        }
    }

}

void DownloadControl::on_pushButton_clicked()
{
    emit stop();
}
