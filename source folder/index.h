#ifndef INDEX_H
#define INDEX_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include "sore.h"
#include "bookmarkinfo.h"
#include "language.h"
class Index : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Index(QWidget *parent);
    enum Type{TreeIndex,TreeSearch};
    void setAllQuran(QMap<int,Sore*> *a);
    void showList();
    void showItemsByFilter(QString filter);
    void setSearchText(QMap<int,QList<QString>* >* list);
    void search(QString s);
    void setTypeTreeWidget(Index::Type t);
    QList<Aye*> getSearchResult();
private:
    Index::Type type;
    QMap<int,Sore*> *allQuran;
    QList<QTreeWidgetItem*> items;
    QMap<int,QList<QString>* >* searchText;
    QList<Aye*> searchResult;
    QTreeWidgetItem *itemContexMenu;
    QList<QString> arabicSigns;
    QList<QString> arabicLetters;
    QList<QString> persianLetters;

    bool showByFilter;
    bool showBySearh;
    QString filter;
    void createList();
    void hiddenItem(bool b);


    void setArabicSigns();
    void setPersianArabicLetters();
    QString replacePersianArabic(QString s);
    QString replaceArabicSigns(QString s);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void clickHandle(QTreeWidgetItem* item,int column);
    void contextMenuHandle(QAction* a);

    void setBackgroundColor(int index, int aye, QString color);

public slots:
    void changeBackgroundColor(int sore, int aye, QString color);





signals:
    void clickedItem(Aye*);
    void updateBookmark(int,int,QString);
    void deleteBookmark(int,int,QString);



};

#endif // INDEX_H
