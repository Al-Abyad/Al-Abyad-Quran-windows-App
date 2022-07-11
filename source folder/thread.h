#ifndef THREAD_H
#define THREAD_H

#include <QThread>

#include "database.h"
#include "aye.h"
#include "qary.h"
#include "global.h"
#include "soredialog.h"
#include "sore.h"
#include "translation.h"
class Thread:public QThread
{
public:


    static Thread *getGlobalThread();

    typedef void (*FuncBookmark)(Aye*,Global::BookmarkOperation);
    typedef void (*FuncQary)(Qary*,Global::qaryOperation);
    typedef void (*FuncExport)(QList<Aye*>,QString,Translation);
    typedef void (*FuncDownload)();
    typedef void (*FuncReadAye)(Aye*);
    void run();
    void setFunc(FuncBookmark f, Aye *a, Global::BookmarkOperation b, Global::ThreadOperation tp);
    void setFunc(FuncQary f, Qary *qr, Global::qaryOperation q, Global::ThreadOperation tp);
    void setFunc(FuncExport f,QList<Aye*> list,QString fileName,Translation trans,Global::ThreadOperation tp);
    void setFunc(FuncDownload f, Global::ThreadOperation tp);
    void setFunc(FuncReadAye f,Aye *a,Global::ThreadOperation tp);


private:

    Thread();//singleton pattern
    static Thread *globalThread;
    FuncBookmark functionBook;
    FuncQary functionQary;
    FuncExport functionExport;
    FuncDownload functionDownload;
    FuncReadAye functionReadAye;
    Aye *aye;
    Qary *qary;
    QList<Aye*> listExport;
    QString fileNameExport;
    Translation transExport;
    Global::BookmarkOperation bookOp;
    Global::qaryOperation qaryOp;
    Global::ThreadOperation threadOp;

    SoreDialog *d;
    Sore *s;
};

#endif // THREAD_H
