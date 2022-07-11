#include "index.h"
#include <QDebug>
Index::Index(QWidget *parent):QTreeWidget(parent)
{

    showByFilter=false;
    filter="All";
    setArabicSigns();
    setPersianArabicLetters();
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(clickHandle(QTreeWidgetItem*,int)));

}


void Index::setAllQuran(QMap<int, Sore *> *a)
{
    allQuran=a;
    createList();

}

void Index::showList()
{

    this->addTopLevelItems(items);

}


void Index::showItemsByFilter(QString filter)
{

    this->filter=filter;

    if(QString::compare(filter,"All")==0){
        showByFilter=false;

        for(int i=0;i<items.count();i++){
            items.at(i)->setHidden(false);
            for(int j=0;j<items.at(i)->childCount();j++){
                items.at(i)->child(j)->setHidden(false);
            }
        }
    }
    else{
        showByFilter=true;

        bool exist;
        for(int i=0;i<items.count();i++){
            exist=false;
            items.at(i)->setHidden(false);
            for(int j=0;j<items.at(i)->childCount();j++){
                int sore=items.at(i)->child(j)->parent()->whatsThis(0).toInt();
                int aye=items.at(i)->child(j)->whatsThis(0).toInt();
                if(sore!=1 && sore!=9){
                    if(QString::compare(allQuran->value(sore)->getAye().at(aye)->getColor(),filter)==0){
                        items.at(i)->child(j)->setHidden(false);
                        exist=true;
                    }
                    else{

                        items.at(i)->child(j)->setHidden(true);

                    }
                }
                else{
                    if(QString::compare(allQuran->value(sore)->getAye().at(aye-1)->getColor(),filter)==0){
                        items.at(i)->child(j)->setHidden(false);
                        exist=true;
                    }
                    else{

                        items.at(i)->child(j)->setHidden(true);

                    }
                }

            }

            if(exist==false)
                items.at(i)->setHidden(true);
        }
    }
}

void Index::setSearchText(QMap<int, QList<QString> *> *list)
{
    searchText=list;
}



void Index::setTypeTreeWidget(Index::Type t)
{
    type=t;
    if(type==TreeSearch){

        this->addTopLevelItems(items);
        hiddenItem(true);
    }

}

QList<Aye *> Index::getSearchResult()
{
    return searchResult;
}



void Index::createList()
{

    Sore *sore;
    QList<Aye*> ayesTemp;
    Aye *tempAye;

    for(int i=1;i<=allQuran->count();i++){
        sore=allQuran->value(i);
        ayesTemp=sore->getAye();
        items.append(new QTreeWidgetItem(QStringList(sore->getName())));
        items.last()->setWhatsThis(0,QString::number(sore->getNumber()));
        items.last()->setIcon(0,QIcon(":/rec/sore.png"));
        items.last()->setSizeHint(0,QSize(items.last()->sizeHint(0).width(),28));
        //ui->textEdit_2->append(sore->getName());
        for(int j=0;j<ayesTemp.count();j++){
            tempAye=ayesTemp.at(j);

            if(tempAye->getChapter()!=1 && tempAye->getChapter()!=9){
                items.last()->addChild(new QTreeWidgetItem(QStringList(QString("%1-"+tempAye->getText()).arg(j))));
                items.last()->child(items.last()->childCount()-1)->setWhatsThis(0,QString::number(j));
            }
            else{
                items.last()->addChild(new QTreeWidgetItem(QStringList(QString("%1-"+tempAye->getText()).arg(j+1))));
                items.last()->child(items.last()->childCount()-1)->setWhatsThis(0,QString::number(j+1));


            }


            items.last()->child(items.last()->childCount()-1)->setIcon(0,QIcon(":/rec/aye.png"));
            items.last()->child(items.last()->childCount()-1)->setSizeHint(0,QSize(items.last()->child(items.last()->childCount()-1)->sizeHint(0).width(),28));
            if(QString::compare(tempAye->getColor(),"blue")!=0){
                if(QString::compare(tempAye->getColor(),"red")==0){
                    items.last()->child(items.last()->childCount()-1)->setBackgroundColor(0,QColor(255,128,128,255));

                }
                else if(QString::compare(tempAye->getColor(),"yellow")==0){
                    items.last()->child(items.last()->childCount()-1)->setBackgroundColor(0,QColor(251,251,128,255));
                }
                else if(QString::compare(tempAye->getColor(),"green")==0){
                    items.last()->child(items.last()->childCount()-1)->setBackgroundColor(0,QColor(134,255,121,255));
                }
            }
                //items.last()->child(items.last()->childCount()-1)->setBackgroundColor(0,QColor(tempAye->getColor()));

            //ui->textEdit_2->append(tempAye->getText());
        }

    }


}

void Index::hiddenItem(bool b)
{
    if(b){
        for(int i=0;i<items.count();i++){
            items.at(i)->setHidden(true);
            for(int j=0;j<items.at(i)->childCount();j++)
                items.at(i)->child(j)->setHidden(true);
        }

    }
    else{
        for(int i=0;i<items.count();i++){
            items.at(i)->setHidden(false);
            for(int j=0;j<items.at(i)->childCount();j++)
                items.at(i)->child(j)->setHidden(false);
        }
        }

}

void Index::clickHandle(QTreeWidgetItem *item, int column)
{
    if(item->childCount()==0){
        int sore=item->parent()->whatsThis(column).toInt();
        int aye=item->whatsThis(column).toInt();

        if(sore!=1 && sore!=9)
            emit clickedItem(allQuran->value(sore)->getAye().at(aye));
        else
            emit clickedItem(allQuran->value(sore)->getAye().at(aye-1));

    }
}

void Index::contextMenuHandle(QAction *a)
{
    int sore=itemContexMenu->parent()->whatsThis(0).toInt();
    int aye=itemContexMenu->whatsThis(0).toInt();

    if(QString::compare(Language::deTranslate(a->text()),"delete")==0){
        if(sore==1 || sore==9)
            setBackgroundColor(this->indexOfTopLevelItem(itemContexMenu->parent()),aye-1,Language::deTranslate(a->text()));
        else
            setBackgroundColor(this->indexOfTopLevelItem(itemContexMenu->parent()),aye,Language::deTranslate(a->text()));

        emit deleteBookmark(sore,aye,"delete");
    }

    else{
        if(sore==1 || sore==9)
            setBackgroundColor(this->indexOfTopLevelItem(itemContexMenu->parent()),aye-1,Language::deTranslate(a->text()));
        else
            setBackgroundColor(this->indexOfTopLevelItem(itemContexMenu->parent()),aye,Language::deTranslate(a->text()));

        emit updateBookmark(sore,aye,Language::deTranslate(a->text()));
    }

    if(QString::compare(filter,"All")!=0)
        showItemsByFilter(filter);

}

void Index::setBackgroundColor(int index, int aye, QString color)
{
    if(QString::compare(color,"delete")==0)
        items.at(index)->child(aye)->setBackgroundColor(0,QColor(Qt::color0));

    else{
        if(QString::compare(color,"red")==0){
            items.at(index)->child(aye)->setBackgroundColor(0,QColor(255,128,128,255));

        }
        else if(QString::compare(color,"yellow")==0){
            items.at(index)->child(aye)->setBackgroundColor(0,QColor(251,251,128,255));
        }
        else if(QString::compare(color,"green")==0){
            items.at(index)->child(aye)->setBackgroundColor(0,QColor(134,255,121,255));
        }
    }



    if(QString::compare(filter,"All")!=0)
        showItemsByFilter(filter);
}

void Index::changeBackgroundColor(int sore, int aye, QString color)
{
    qDebug()<<"ddcccccol "<<color;
    if(QString::compare(color,"delete")==0){
        if(sore!=1 && sore!=9)
            items.at(sore-1)->child(aye)->setBackgroundColor(0,QColor(Qt::color0));
        else
            items.at(sore-1)->child(aye-1)->setBackgroundColor(0,QColor(Qt::color0));
    }


    else if(QString::compare(color,"read")!=0){
        if(sore!=1 && sore!=9){
            if(QString::compare(color,"red")==0){
                items.at(sore-1)->child(aye)->setBackgroundColor(0,QColor(255,128,128,255));
            }
            else if(QString::compare(color,"yellow")==0){
                items.at(sore-1)->child(aye)->setBackgroundColor(0,QColor(251,251,128,255));
            }
            else if(QString::compare(color,"green")==0){
                items.at(sore-1)->child(aye)->setBackgroundColor(0,QColor(134,255,121,255));
            }

        }

        else{
            if(QString::compare(color,"red")==0){
                items.at(sore-1)->child(aye-1)->setBackgroundColor(0,QColor(255,128,128,255));
            }
            else if(QString::compare(color,"yellow")==0){
                items.at(sore-1)->child(aye-1)->setBackgroundColor(0,QColor(251,251,128,255));
            }
            else if(QString::compare(color,"green")==0){
                items.at(sore-1)->child(aye-1)->setBackgroundColor(0,QColor(134,255,121,255));
            }
        }

    }

    if(QString::compare(filter,"All")!=0)
        showItemsByFilter(filter);

}


void Index::contextMenuEvent(QContextMenuEvent *event){

    if(this->itemAt(event->pos())){
        if(this->itemAt(event->pos())->childCount()==0){
            itemContexMenu=this->itemAt(event->pos());
            QMenu *menu=new QMenu();
            menu->addAction(QIcon(":/rec/icon/014_060_add_product_crate_package_box_parcel_shipping_bundle_cargo.png"),Language::translate("read"));
            menu->addAction(QIcon(":/rec/icon/022_025_layers_front_copy_clone.png"),Language::translate("copy"));
            menu->addAction(QIcon(":/rec/green.png"),Language::translate("green"));
            menu->addAction(QIcon(":/rec/yellow.png"),Language::translate("yellow"));
            menu->addAction(QIcon(":/rec/red.png"),Language::translate("red"));
            menu->addAction(QIcon(":/rec/icon/024_141_cancel_stop_cancellation_forbidden.png"),Language::translate("delete"));

            connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(contextMenuHandle(QAction*)));
            menu->exec(this->viewport()->mapToGlobal(event->pos()));
        }
    }

}

void Index::search(QString s)
{
    qDebug()<<"searchh "<<s;
    searchResult.clear();
    hiddenItem(true);
    QString completeText;
    if(QString::compare(s,"")==0 && type==TreeIndex){
        hiddenItem(false);
    }
    else if(QString::compare(s,"")==0 && type==TreeSearch){
        hiddenItem(true);
    }
    else{
        for(int i=searchText->keys().first();i<=searchText->keys().last();i++){
            for(int j=0;j<searchText->value(i)->count();j++){

                completeText=searchText->value(i)->at(j);

                if(Language::getKeyBoardLanguage()==Global::Persian)
                    completeText=replacePersianArabic(completeText);
                else if(Language::getKeyBoardLanguage()==Global::Arabic)
                    completeText=replaceArabicSigns(completeText);
                if(completeText.contains(s)){
                    //qDebug()<<"searchhtxt "<<completeText;
                    items.at(i-searchText->keys().first())->setHidden(false);
                    items.at(i-searchText->keys().first())->child(j)->setHidden(false);
                    searchResult.append(allQuran->value(i)->getAye().at(j));
                }
            }

        }

    }
}


void Index::setArabicSigns(){

    arabicSigns.append(QString::fromUtf8("\u061A"));
    arabicSigns.append(QString::fromUtf8("\u065A"));



    arabicSigns.append(QString::fromUtf8("\u064B"));
    arabicSigns.append(QString::fromUtf8("\u065B"));
    arabicSigns.append(QString::fromUtf8("\u06DB"));
    arabicSigns.append(QString::fromUtf8("\u06EB"));


    arabicSigns.append(QString::fromUtf8("\u064C"));


    arabicSigns.append(QString::fromUtf8("\u064D"));
    arabicSigns.append(QString::fromUtf8("\u065D"));

    arabicSigns.append(QString::fromUtf8("\u061E"));
    arabicSigns.append(QString::fromUtf8("\u064E"));
    arabicSigns.append(QString::fromUtf8("\u065E"));


    arabicSigns.append(QString::fromUtf8("\u064F"));
    arabicSigns.append(QString::fromUtf8("\u065F"));
    arabicSigns.append(QString::fromUtf8("\u06DF"));

    arabicSigns.append(QString::fromUtf8("\u0610"));
    arabicSigns.append(QString::fromUtf8("\u0650"));

    arabicSigns.append(QString::fromUtf8("\u0611"));
    arabicSigns.append(QString::fromUtf8("\u0651"));

    arabicSigns.append(QString::fromUtf8("\u0612"));
    arabicSigns.append(QString::fromUtf8("\u0652"));

    arabicSigns.append(QString::fromUtf8("\u0613"));
    arabicSigns.append(QString::fromUtf8("\u0653"));

    arabicSigns.append(QString::fromUtf8("\u0614"));
    arabicSigns.append(QString::fromUtf8("\u0654"));

    arabicSigns.append(QString::fromUtf8("\u0616"));
    arabicSigns.append(QString::fromUtf8("\u0656"));

    arabicSigns.append(QString::fromUtf8("\u0618"));
    arabicSigns.append(QString::fromUtf8("\u0658"));

    arabicSigns.append(QString::fromUtf8("\u0619"));
    arabicSigns.append(QString::fromUtf8("\u0659"));


    arabicSigns.append(QString::fromUtf8("\u0670"));


}


void Index::setPersianArabicLetters(){

    arabicLetters.append(QString::fromUtf8("\u0620"));
    persianLetters.append(QString::fromUtf8("\u06CC"));

    arabicLetters.append(QString::fromUtf8("\u0623"));
    persianLetters.append(QString::fromUtf8("\u0627"));

    arabicLetters.append(QString::fromUtf8("\u0624"));
    persianLetters.append(QString::fromUtf8("\u06CC"));

    arabicLetters.append(QString::fromUtf8("\u0625"));
    persianLetters.append(QString::fromUtf8("\u0627"));

    arabicLetters.append(QString::fromUtf8("\u0626"));
    persianLetters.append(QString::fromUtf8("\u06CC"));

    arabicLetters.append(QString::fromUtf8("\u0629"));
    persianLetters.append(QString::fromUtf8("\u0647"));

    arabicLetters.append(QString::fromUtf8("\u0643"));
    persianLetters.append(QString::fromUtf8("\u06A9"));

    arabicLetters.append(QString::fromUtf8("\u064A"));
    persianLetters.append(QString::fromUtf8("\u06CC"));

    arabicLetters.append(QString::fromUtf8("\u0673"));
    persianLetters.append(QString::fromUtf8("\u0627"));

    arabicLetters.append(QString::fromUtf8("\u0672"));
    persianLetters.append(QString::fromUtf8("\u0627"));

    arabicLetters.append(QString::fromUtf8("\u0676"));
    persianLetters.append(QString::fromUtf8("\u0648"));

    arabicLetters.append(QString::fromUtf8("\u06C3"));
    persianLetters.append(QString::fromUtf8("\u06C9"));

    arabicLetters.append(QString::fromUtf8("\u064A"));
    persianLetters.append(QString::fromUtf8("\u06CC"));

    arabicLetters.append(QString::fromUtf8("\u0678"));
    persianLetters.append(QString::fromUtf8("\u06CC"));


//    arabicLetters.append(QString::fromUtf8("");
//    persianLetters.append(QString::fromUtf8("");

//    arabicLetters.append(QString::fromUtf8("");
//    persianLetters.append(QString::fromUtf8("");

//    arabicLetters.append(QString::fromUtf8("");
//    persianLetters.append(QString::fromUtf8("");


}


QString Index::replacePersianArabic(QString s){
    QString result=s;

    //qDebug()<<"tttt "<<s;


    for(int i=0;i<persianLetters.count();i++){
        result.replace(arabicLetters.at(i),persianLetters.at(i));
    }

    return result;
}

QString Index::replaceArabicSigns(QString s){
    QString result=s;
    for(int i=0;i<arabicSigns.count();i++){
        result.remove(arabicSigns.at(i));
    }


    return result;
}


