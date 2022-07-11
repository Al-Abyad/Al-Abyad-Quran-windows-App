#include "bookmark.h"

Bookmark::Bookmark(QWidget *parent):QTableWidget(parent)
{
    this->horizontalHeader()->setStretchLastSection(true);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);



    connect(this,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(clickItemHandle(QTableWidgetItem*)));
    connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(doubleClickHandle(QTableWidgetItem*)));
}

void Bookmark::setBookmarks(QList<Aye *> *b)
{

    bookmarks=b;
    showBookmark();
}



void Bookmark::showBookmark()
{

    bookmarkItems.clear();
    this->clear();





    this->setColumnCount(6);
    QTableWidgetItem *item1=new QTableWidgetItem;
    QTableWidgetItem *item2=new QTableWidgetItem;
    QTableWidgetItem *item3=new QTableWidgetItem;
    QTableWidgetItem *item4=new QTableWidgetItem;
    QTableWidgetItem *item5=new QTableWidgetItem;
    QTableWidgetItem *item6=new QTableWidgetItem;



    item1->setText(Language::translate("grade"));
    item2->setText(Language::translate("sound"));
    item3->setText(Language::translate("sore"));
    item4->setText(Language::translate("aye"));
    item5->setText(Language::translate("page"));
    item6->setText(Language::translate("text"));





    this->setHorizontalHeaderItem(0,item1);
    this->setHorizontalHeaderItem(1,item2);
    this->setHorizontalHeaderItem(2,item3);
    this->setHorizontalHeaderItem(3,item4);
    this->setHorizontalHeaderItem(4,item5);
    this->setHorizontalHeaderItem(5,item6);




    this->setRowCount(bookmarks->count());

    Aye *tempAye;
    QList<QTableWidgetItem*> tmpItem;
    for(int i=0;i<bookmarks->count();i++){
        tmpItem=QList<QTableWidgetItem*>();
        tempAye=bookmarks->at(i);

        tmpItem.append(new QTableWidgetItem(QIcon(QString(":/rec/%1.png").arg(tempAye->getColor())),""));
        tmpItem.last()->setWhatsThis(QString::number(i));//index of bookmark in bookmark list
        tmpItem.last()->setTextAlignment(Qt::AlignCenter);
        this->setItem(i,0,tmpItem.last());

        tmpItem.append(new QTableWidgetItem("   "));
        tmpItem.last()->setWhatsThis(QString::number(i));
        tmpItem.last()->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        tmpItem.last()->setTextAlignment(Qt::AlignCenter);
        this->setItem(i,1,tmpItem.last());

        tmpItem.append(new QTableWidgetItem(tempAye->getSoreName()));
        tmpItem.last()->setWhatsThis(QString::number(i));
        tmpItem.last()->setTextAlignment(Qt::AlignCenter);
        this->setItem(i,2,tmpItem.last());

        tmpItem.append(new QTableWidgetItem(QString::number(tempAye->getVerse())));
        tmpItem.last()->setWhatsThis(QString::number(i));
        tmpItem.last()->setTextAlignment(Qt::AlignCenter);
        this->setItem(i,3,tmpItem.last());

        tmpItem.append(new QTableWidgetItem(QString::number(tempAye->getPage())));
        tmpItem.last()->setWhatsThis(QString::number(i));
        tmpItem.last()->setTextAlignment(Qt::AlignCenter);
        this->setItem(i,4,tmpItem.last());

        tmpItem.append(new QTableWidgetItem(tempAye->getText()));
        tmpItem.last()->setWhatsThis(QString::number(i));
        tmpItem.last()->setTextAlignment(Qt::AlignCenter);



        this->setItem(i,5,tmpItem.last());


        bookmarkItems.insert(i,tmpItem);

    }




}

void Bookmark::resetPlayIconItems()
{
    for(int i=0;i<bookmarkItems.count();i++)
        bookmarkItems.value(i).at(1)->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}



void Bookmark::contextMenuEvent(QContextMenuEvent *event){
    if(this->itemAt(event->pos())->column()!=-1 && this->itemAt(event->pos())->row()!=-1){
        itemContexMenu=this->itemAt(event->pos());
        QMenu *menu=new QMenu();
        menu->addAction(QIcon(":/rec/green.png"),Language::translate("green"));
        menu->addAction(QIcon(":/rec/yellow.png"),Language::translate("yellow"));
        menu->addAction(QIcon(":/rec/red.png"),Language::translate("red"));
        menu->addAction(QIcon(":/rec/icon/024_141_cancel_stop_cancellation_forbidden.png"),Language::translate("delete"));

        connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(contextMenuHandle(QAction*)));

        menu->exec(this->viewport()->mapToGlobal(event->pos()));
    }

}

void Bookmark::handleEndBookmarkPlay()
{
    resetPlayIconItems();
}

void Bookmark::contextMenuHandle(QAction *a)
{
    int index=itemContexMenu->whatsThis().toInt();
    int sore=bookmarks->at(index)->getChapter();
    int aye=bookmarks->at(index)->getVerse();
    if(QString::compare(Language::deTranslate(a->text()),"delete")==0){

        emit deleteBookmark(sore,aye,"delete");
    }
    else{
        emit updateBoomark(sore,aye,Language::deTranslate(a->text()));
    }
}

void Bookmark::clickItemHandle(QTableWidgetItem *item)
{

    if(this->column(item)==1){

        int index=item->whatsThis().toInt();
        resetPlayIconItems();
        item->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
        emit playBookmark(bookmarks->at(index));
    }

}

void Bookmark::doubleClickHandle(QTableWidgetItem *item)
{
    int index=item->whatsThis().toInt();


    emit clickedDoubleItem(bookmarks->at(index));
}
