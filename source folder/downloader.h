#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QList>
#include <QQueue>
#include <QFile>
#include <QByteArray>
#include <QDataStream>
#include <QTimer>
#include "downloadinfo.h"





class Downloader:public QObject
{

    Q_OBJECT

public:
    Downloader();

    void addDownload(QList<DownloadInfo*> l);

public slots:
    void stopDownload();



private:
    QNetworkAccessManager *netManager;
    QNetworkReply *repRequest;
    QQueue<DownloadInfo*> *downloadList;
    QTimer *timer;
    DownloadInfo *currentDownload;
    bool downloading;

    void download();
    bool checkExistDownloadInfo(DownloadInfo *a);


private slots:
    void fileDownloaded(QNetworkReply* rep);
    void httpFinished();
    void handleError(QNetworkReply::NetworkError e);
    void emitSavedFile();

    void recievedBytes(qint64 received, qint64 total);


signals:
    void downloaded(DownloadInfo*);
    void updatedDownloadList(QQueue<DownloadInfo*>*);
    void report(QString);
    void bytesReceived(qint64,qint64);
};

#endif // DOWNLOADER_H
