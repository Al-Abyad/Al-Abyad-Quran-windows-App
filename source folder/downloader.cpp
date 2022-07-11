#include "downloader.h"

Downloader::Downloader()
{
    downloading=false;
    downloadList=new QQueue<DownloadInfo*>();
    timer=new QTimer();
}

void Downloader::addDownload(QList<DownloadInfo *> l)
{

//    for(int i=0;i<l.count();i++)
//        downloadList->enqueue(l.at(i));

    for(int i=0;i<l.count();i++)
        if(!checkExistDownloadInfo(l.at(i)))
            downloadList->append(l.at(i));


    emit updatedDownloadList(downloadList);
    if(!downloading)
        download();


}



void Downloader::download()
{

    if(downloadList->empty())
        return;

   while(QFile::exists(downloadList->head()->getSavePath())){

       downloadList->dequeue();
       if(downloadList->empty())
           return;
   }

    currentDownload=downloadList->dequeue();

    netManager=new QNetworkAccessManager(this);
    repRequest=netManager->get(QNetworkRequest(QUrl(currentDownload->getUrl())));
    downloading=true;

    connect(netManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(fileDownloaded(QNetworkReply*)));

    connect(repRequest,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(recievedBytes(qint64,qint64)));
    connect(repRequest,SIGNAL(finished()),this,SLOT(httpFinished()));
    connect(repRequest,SIGNAL(error(QNetworkReply::NetworkError)),this,
            SLOT(handleError(QNetworkReply::NetworkError)));

    emit report("downloading");



}

bool Downloader::checkExistDownloadInfo(DownloadInfo *a)
{
    for(int i=0;i<downloadList->count();i++)
        if(QString::compare(a->getSavePath(),downloadList->at(i)->getSavePath())==0)
            return true;

    return false;
}

void Downloader::fileDownloaded(QNetworkReply *rep)
{
    if(rep->error() ==QNetworkReply::NoError){
        QByteArray downloadData = rep->readAll();

        QFile file(currentDownload->getSavePath());
        file.open(QIODevice::WriteOnly);
        QDataStream dataStream(&file);
        dataStream<<downloadData;
        file.close();
        rep->deleteLater();
        repRequest->deleteLater();
        netManager->deleteLater();


        timer->singleShot(1000,this,SLOT(emitSavedFile()));


    }

}


void Downloader::emitSavedFile()
{

    emit downloaded(currentDownload);

    emit updatedDownloadList(downloadList);
    if(downloadList->empty()){
        downloading=false;
        emit report("downloaded");

    }
    else
        download();


}

void Downloader::recievedBytes(qint64 received, qint64 total)
{
    emit bytesReceived(received,total);
}

void Downloader::httpFinished()
{

    if(repRequest->error()){



        if(repRequest->error()==QNetworkReply::ConnectionRefusedError)
            emit report("serverError");
        else if(repRequest->error()==QNetworkReply::HostNotFoundError)
            emit report("internetConnectionError");
        else if(repRequest->error()==QNetworkReply::ContentNotFoundError)
            emit report("contentError");


        downloading=false;
        repRequest->deleteLater();
        repRequest=0;
        netManager->deleteLater();
        netManager=0;

        downloadList->clear();

        emit updatedDownloadList(downloadList);

    }

}

void Downloader::handleError(QNetworkReply::NetworkError e)
{

    downloading=false;

    if(e==QNetworkReply::ConnectionRefusedError)
        emit report("serverError");
    else if(e==QNetworkReply::HostNotFoundError)
        emit report("internetConnectionError");
    else if(e==QNetworkReply::ContentNotFoundError)
        emit report("contentError");

    downloadList->clear();
    emit updatedDownloadList(downloadList);

}


void Downloader::stopDownload()
{
    if( downloading && repRequest!=0){
        downloading=false;

        downloadList->clear();
        delete repRequest;
        repRequest=0;
        delete netManager;
        netManager=0;

        emit updatedDownloadList(downloadList);
        emit report("");

    }


}




