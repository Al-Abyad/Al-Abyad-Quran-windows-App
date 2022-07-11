#ifndef DOWNLOADINFO_H
#define DOWNLOADINFO_H

#include <QString>
#include <QVariant>
class DownloadInfo
{
public:
    DownloadInfo();

    virtual QString getUrl();
    virtual QString getSavePath();
    virtual QMap<QString,QVariant> getFileInfo();

protected:

    QMap<QString,QVariant> fileInfo;

};

#endif // DOWNLOADINFO_H
