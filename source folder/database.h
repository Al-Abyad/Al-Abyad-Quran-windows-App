#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "aye.h"
#include "sore.h"
#include "bookmarkinfo.h"
#include "qary.h"
#include "global.h"
#include "translation.h"

class Database
{
public:
    Database();
    QMap<int, Sore *> *getListAllSore();
    QList<BookmarkInfo> getBookmarks();
    QList<Qary*> *getQary();
    QMap<int,QMap<QString,int> > getJuz();

    QMap<QString, QList<Translation> *> *getLangTranList();
    QMap<int,QList<QString> > getTranslation(Translation t);
    QMap<int,QList<QString>* > *getSearchText();

    static void updateBookmark(Aye *a, Global::BookmarkOperation bookmarkOp);
    static void updateQary(Qary *q,Global::qaryOperation qaryOp);
    static QString getTranslation(Translation t, Aye *a);
    static void saveReadStatus(Aye *a);

private:
   static QSqlDatabase db;
};

#endif // DATABASE_H
