#ifndef DOWNLOADCONTROL_H
#define DOWNLOADCONTROL_H

#include <QDialog>
#include <QQueue>
#include <QListWidgetItem>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include "downloadinfo.h"
#include "language.h"
namespace Ui {
class DownloadControl;
}

class DownloadControl : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadControl(QWidget *parent = 0);
    ~DownloadControl();

public slots:
    void setDownloadList(QQueue<DownloadInfo*> *list);
    void setTextWidgets();
    void reciveCurrentDownload(qint64 bytesReceived, qint64 bytesTotal);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DownloadControl *ui;
    QProgressBar *itemProgrss;
    QQueue<DownloadInfo*> downloadList;
    int count;

signals:
    void stop();

};

#endif // DOWNLOADCONTROL_H
