#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
#include <QHeaderView>
#include <QMouseEvent>
#include <QMenu>
#include "aye.h"
#include "language.h"
#include <QDebug>
class Bookmark:public QTableWidget
{
    Q_OBJECT

public:
    explicit Bookmark(QWidget *parent);
    void setBookmarks(QList<Aye*> *b);
    void showBookmark();


private:
    QList<Aye*> *bookmarks;
    QMap<int,QList<QTableWidgetItem*> > bookmarkItems;//key is index of bookmark list
    QTableWidgetItem *itemContexMenu;

    void resetPlayIconItems();



protected:

    void contextMenuEvent(QContextMenuEvent *event);


public slots:
    void handleEndBookmarkPlay();
private slots:
    void contextMenuHandle(QAction* a);
    void clickItemHandle(QTableWidgetItem *item);
    void doubleClickHandle(QTableWidgetItem *item);

signals:
    void updateBoomark(int,int,QString);
    void deleteBookmark(int,int,QString);
    void clickedDoubleItem(Aye*);
    void playBookmark(Aye*);

};

#endif // BOOKMARK_H
