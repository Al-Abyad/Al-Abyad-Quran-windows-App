#ifndef DOWNLOADINFOQURAN_H
#define DOWNLOADINFOQURAN_H

#include "downloadinfo.h"
#include "aye.h"
#include "qary.h"
class DownloadInfoQuran:public DownloadInfo
{

public:
    explicit DownloadInfoQuran();
    DownloadInfoQuran(Qary *q,Aye *a);

    QString getUrl();
    QString getSavePath();
    Aye* getAye();
    Qary* getQary();

private:
    Qary *qary;
    Aye *aye;


};

#endif // DOWNLOADINFOQURAN_H
