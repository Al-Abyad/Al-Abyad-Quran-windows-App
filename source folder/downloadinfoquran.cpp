#include "downloadinfoquran.h"

DownloadInfoQuran::DownloadInfoQuran():DownloadInfo()
{

}

DownloadInfoQuran::DownloadInfoQuran(Qary *q, Aye *a):DownloadInfo()
{
    qary=q;
    aye=a;


}

QString DownloadInfoQuran::getUrl()
{
    return qary->getUrl()+QString("%1.mp3").arg(aye->getAudio());
}

QString DownloadInfoQuran::getSavePath()
{
    return "Audio//"+qary->getDir()+"//"+QString("%1.mp3").arg(aye->getAudio());
}



Aye *DownloadInfoQuran::getAye()
{
    return aye;
}

Qary *DownloadInfoQuran::getQary()
{
    return qary;
}

