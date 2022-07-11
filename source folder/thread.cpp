#include "thread.h"

Thread* Thread::globalThread;

Thread::Thread():QThread()
{

}

void Thread::setFunc(FuncBookmark f, Aye *a, Global::BookmarkOperation b, Global::ThreadOperation tp)
{
    functionBook=f;
    aye=a;
    bookOp=b;
    threadOp=tp;


}

void Thread::setFunc(FuncQary f, Qary *qr, Global::qaryOperation q, Global::ThreadOperation tp)
{
    functionQary=f;
    qary=qr;
    qaryOp=q;
    threadOp=tp;
}

void Thread::setFunc(Thread::FuncExport f, QList<Aye *> list
                     , QString fileName, Translation trans, Global::ThreadOperation tp)
{
    functionExport=f;
    listExport=list;
    fileNameExport=fileName;
    transExport=trans;
    threadOp=tp;
}

void Thread::setFunc(FuncDownload f,Global::ThreadOperation tp)
{
    functionDownload=f;
    threadOp=tp;
}

void Thread::setFunc(Thread::FuncReadAye f, Aye *a, Global::ThreadOperation tp)
{
    functionReadAye=f;
    aye=a;
    threadOp=tp;
}



Thread *Thread::getGlobalThread()
{
    if(globalThread==0)
        globalThread=new Thread();
    return globalThread;
}

void Thread::run()
{
    if(threadOp==Global::DBBookMarkThreadOP)
        (*functionBook)(aye,bookOp);
    else if(threadOp==Global::DBQaryThreadOP)
        (*functionQary)(qary,qaryOp);
    else if(threadOp==Global::Export)
        (*functionExport)(listExport,fileNameExport,transExport);
    else if(threadOp==Global::Download)
        (*functionDownload)();
    else if(threadOp==Global::DBReadAye)
        (*functionReadAye)(aye);

    qDebug()<<"runnnn";
}

//void Thread::setFunc(void (MainWindow::function)())
//{
//   // this->func=function;
//}

