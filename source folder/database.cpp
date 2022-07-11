#include "database.h"

#include "ayecordinate.h"

QSqlDatabase Database::db;

Database::Database()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mhd.db");

    if( !db.open() )
      {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
      }

      qDebug( "Connected!" );

}

QMap<int,Sore*>* Database::getListAllSore()
{

    int sore=1,aye=1,currentSore,currentAye;

    QSqlQuery quran,cordiante,property;
    quran.prepare("SELECT * FROM Quran");
    cordiante.prepare("SELECT * FROM Cordinate ORDER BY page ASC");
    property.prepare("SELECT * FROM ChapterProperty");

    qDebug()<<quran.exec();
    qDebug()<<cordiante.exec();
    qDebug()<<property.exec();


    QList<QList<QList<AyeCordinate> > > listCordinate;
    QList<QList<AyeCordinate> > soreCordinate;
    QList<AyeCordinate> ayeCordinate;


    AyeCordinate tempCorAye;

    currentSore=1;
    currentAye=1;
    while(cordiante.next()){

        sore=cordiante.value("numsore").toInt();
        aye=cordiante.value("ayeSore").toInt();

        if(sore!=currentSore){
            soreCordinate.append(ayeCordinate);
            if(sore!=1 && sore!=9)
                currentAye=0;
            else
                currentAye=1;
            ayeCordinate.clear();
            listCordinate.append(soreCordinate);
            currentSore=sore;
            soreCordinate.clear();


        }

        if(aye!=currentAye){
            soreCordinate.append(ayeCordinate);
            currentAye=aye;
            ayeCordinate.clear();

        }


            tempCorAye.setHeight(cordiante.value("height").toInt());
            tempCorAye.setLine(cordiante.value("line").toInt());
            tempCorAye.setWidth(cordiante.value("width").toInt());
            tempCorAye.setXb(cordiante.value("xb").toInt());
            tempCorAye.setXe(cordiante.value("xe").toInt());
            tempCorAye.setyb(cordiante.value("yb").toInt());
            ayeCordinate.append(tempCorAye);
            tempCorAye=AyeCordinate();




            if(currentSore==114 && aye==6){
                soreCordinate.append(ayeCordinate);

                if(sore!=1)
                    currentAye=0;
                ayeCordinate.clear();

                listCordinate.append(soreCordinate);

                currentSore=sore;
                soreCordinate.clear();
            }


    }





    QList<QList<Aye*> > tempAllAye;
    QList<Aye*> tempListAye;
    Aye *ayeTemp;
    currentSore=1;
    currentAye=1;
    int index=0;
    while(quran.next()){
        sore=quran.value("Chapter").toInt();
        aye=quran.value("Verse").toInt();

        if(sore!=currentSore){
            //qlist.at(currentSore-1).setAye(tempListAye);
            tempAllAye.append(tempListAye);
            currentSore=sore;
            //qDebug()<<tempListAye.count();
            tempListAye.clear();
            index=0;

        }

        if(sore<=114 && sore>0){
            ayeTemp=new Aye();
            ayeTemp->setAudio(quran.value("audio").toString());
            ayeTemp->setChapter(sore);
            ayeTemp->setColor(quran.value("color").toString());
            ayeTemp->setJuz(quran.value("Juz").toInt());
            ayeTemp->setPage(quran.value("Page").toInt());
            ayeTemp->setText(quran.value("Arabic").toString());
            ayeTemp->setAyePage(quran.value("ayePage").toInt());
            ayeTemp->setNumLine(quran.value("numline").toInt());
            ayeTemp->setVerse(aye);
            ayeTemp->setAyeQuran(quran.value("id").toInt());
            ayeTemp->setCordinate(listCordinate.at(sore-1).at(index));
            ayeTemp->setReadDate(quran.value("readDate").toLongLong());
            ayeTemp->setReadCount(quran.value("readCount").toInt());

            tempListAye.append(ayeTemp);

            index++;
        }



        if(currentSore==114 && aye==6){
            tempAllAye.append(tempListAye);
            currentSore=sore;
            //qDebug()<<tempListAye.count();
            tempListAye.clear();
            index=0;
        }

    }



    QList<Sore*> qlist;
    Sore *tempQ;
    int i=0;

    qDebug()<<tempAllAye.count();
    while(property.next()){
        tempQ=new Sore();
        tempQ->setNumber(property.value("Id").toInt());
        tempQ->setName(property.value("Name").toString());
        tempQ->setVerse(property.value("Verse").toInt());
        tempQ->setAye(tempAllAye.at(i));
        tempQ->setLocNozol(property.value("Nozol").toString());
        tempQ->setTratibNozol(property.value("revel").toString());
        tempQ->setEnName(property.value("descent").toString());
        tempQ->setFazl(property.value("fazl").toString());
        tempQ->setBarekat(property.value("barekat").toString());
        tempQ->setTrans(property.value("trans").toString());
        qlist.append(tempQ);
        i++;

    }




    QMap<int,Sore*> *result=new QMap<int,Sore*>();

    for(int i=0;i<qlist.count();i++){
        result->insert(qlist.at(i)->getNumber(),qlist.at(i));
    }



    return result;




}

QList<BookmarkInfo> Database::getBookmarks()
{
    QList<BookmarkInfo> bookmarks;
    QSqlQuery query;
    query.prepare("SELECT chapter,verse FROM bookMarks ");

    qDebug()<<query.exec();

    while(query.next()){
        bookmarks.append(BookmarkInfo());
        bookmarks.last().setSore(query.value("chapter").toInt());
        bookmarks.last().setAye(query.value("verse").toInt());
    }

    return bookmarks;

}

QList<Qary *> *Database::getQary()
{
    QList<Qary*> *list=new QList<Qary*>();
    QSqlQuery query;
    query.prepare("SELECT * FROM Audio ");

    qDebug()<<query.exec();

    while(query.next()){
        list->append(new Qary());
        list->last()->setName(query.value("Name").toString());
        list->last()->setDir(query.value("dir_Name").toString());
        list->last()->setUrl(query.value("Url").toString());
        list->last()->setType(query.value("type").toString());
        list->last()->setId(query.value("id").toInt());

    }

    return list;

}

QMap<int, QMap<QString, int> > Database::getJuz()
{
    QMap<int, QMap<QString, int> > list;
    QSqlQuery query;
    query.prepare("SELECT Chapter ,Verse as Verse,Juz FROM (SELECT min(Chapter) as Chapter ,Verse as Verse,Juz FROM Quran GROUP BY Juz) GROUP BY Juz ");

    qDebug()<<query.exec();

    int chapter,verse;
    QMap<QString, int> temp;
    while(query.next()){

        chapter=query.value("Chapter").toInt();
        verse=query.value("Verse").toInt();

        if(chapter==2 && verse==0){
            temp.insert("aye",verse+1);
            chapter=1;
        }
        else{
            temp.insert("aye",verse);
        }

        temp.insert("sore",chapter);

        list.insert(query.value("Juz").toInt(),temp);

        temp=QMap<QString, int>();

    }

    return list;

}

QMap<QString, QList<Translation>* >* Database::getLangTranList()
{

    QMap<QString, QList<Translation>* >* list=new QMap<QString, QList<Translation>* >();
    QSqlQuery qLang;
    qLang.prepare("SELECT language,translator,name,lang FROM translation ");

    qDebug()<<qLang.exec();


    QString lang;
    while(qLang.next()){
        lang=qLang.value("lang").toString();
        if(list->value(lang)==0){
            list->insert(lang,new QList<Translation>());
        }
        Translation t;
        t.setTranslator(qLang.value("translator").toString());
        t.setName(qLang.value("name").toString());
        t.setLanguage(qLang.value("language").toString());
        list->value(lang)->append(t);

    }

    return list;
}

QMap<int,QList<QString> > Database::getTranslation(Translation t)
{
    QMap<int,QList<QString> > list;
    QList<QString> temp;
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM `"+t.getLanguage()+"."+t.getTranslator())+"`;");

    qDebug()<<query.exec();
    qDebug()<<query.lastError();



    int currentSore=1;
    int preSore=1;
    while(query.next()){
        currentSore=query.value("sore").toInt();
        if(currentSore!=preSore){
            list.insert(preSore,temp);
            temp=QList<QString>();
            preSore=currentSore;
        }
        temp.append(query.value("text").toString());

        if(currentSore==114 && query.value("aye").toInt()==6){
            list.insert(preSore,temp);
            temp=QList<QString>();
            preSore=currentSore;
        }

    }

    return list;
}

QMap<int, QList<QString>* > *Database::getSearchText()
{
    QMap<int, QList<QString>* > *list=new QMap<int, QList<QString>* >();
    QSqlQuery query;
    query.prepare("SELECT * FROM quran_search;");

    qDebug()<<query.exec();
    int soreNow,sorePre;
    bool start=false;
    QList<QString> *temp=new QList<QString>();
    while(query.next()){
        if(!start){
            soreNow=query.value("sure").toInt();
            sorePre=soreNow;
            start=true;
        }
        else
            soreNow=query.value("sure").toInt();
        if(soreNow==114){
            qDebug()<<"";
        }

        if(soreNow!=sorePre){
            list->insert(sorePre,temp);
            sorePre=soreNow;

            temp=new QList<QString>();

        }
        temp->append(query.value("text").toString());
    }

    list->insert(sorePre,temp);
    return list;
}


void Database::updateBookmark(Aye *a,Global::BookmarkOperation bookmarkOp)
{
    QSqlQuery book,quran,cordiante;

    if(bookmarkOp==Global::SaveBookmark){
        book.prepare("INSERT INTO BookMarks (chapter,verse,color,page,text,soreName)"
                  "VALUES(:sore,:aye,:color,:page,:text,:soreName);");
        book.bindValue(":page",a->getPage());
        book.bindValue(":text",a->getText());
        book.bindValue(":soreName",a->getSoreName());
        book.bindValue(":color",a->getColor());
    }
    else if(bookmarkOp==Global::UpdateBookmark){
        book.prepare("UPDATE BookMarks SET color=:color WHERE chapter=:sore AND verse=:aye;");
        book.bindValue(":color",a->getColor());

    }
    else if(bookmarkOp==Global::DeleteBookmark)
        book.prepare("DELETE FROM BookMarks WHERE chapter=:sore AND verse=:aye;");

    book.bindValue(":sore",a->getChapter());
    book.bindValue(":aye",a->getVerse());


    quran.prepare("UPDATE Quran SET color=:color WHERE Chapter=:sore AND Verse=:aye;");
    cordiante.prepare("UPDATE Cordinate SET color=:color WHERE numsore=:sore AND ayeSore=:aye");





    quran.bindValue(":sore",a->getChapter());
    quran.bindValue(":aye",a->getVerse());
    quran.bindValue(":color",a->getColor());

    cordiante.bindValue(":sore",a->getChapter());
    cordiante.bindValue(":aye",a->getVerse());
    cordiante.bindValue(":color",a->getColor());

    qDebug()<<book.exec()<<book.lastError();
    qDebug()<<quran.exec()<<quran.lastError();
    qDebug()<<cordiante.exec()<<cordiante.lastError();



}

void Database::updateQary(Qary *q, Global::qaryOperation qaryOp)
{
    QSqlQuery query;
    if(qaryOp==Global::SaveQary){
        query.prepare("INSERT INTO Audio (Name,dir_Name,type)VALUES(:name,:dir,:type);");

        query.bindValue(":name",q->getName());
        query.bindValue(":dir",q->getDir());
        query.bindValue(":type",q->getType());

    }
    else if(qaryOp==Global::UpdateQary){
        query.prepare("UPDATE Audio set Name=:name,dir_Name=:dir,type=:type WHERE id=:id");

        query.bindValue(":name",q->getName());
        query.bindValue(":dir",q->getDir());
        query.bindValue(":type",q->getType());
        query.bindValue(":id",q->getId());
    }

    else if(qaryOp==Global::DeleteQary){
        query.prepare("DELETE FROM Audio WHERE id=:id");

        query.bindValue(":id",q->getId());
    }

    qDebug()<<query.exec()<<query.lastError();

}

QString Database::getTranslation(Translation t, Aye *a)
{
    QSqlQuery q;
    q.prepare(QString("SELECT text FROM `"+t.getLanguage()+"."+t.getTranslator()+"` WHERE sore=:sore AND aye=:aye")
              .arg(t.getLanguage(),t.getTranslator()));
    q.bindValue(":sore",a->getChapter());
    q.bindValue(":aye",a->getVerse());

    qDebug()<<q.exec();


    while(q.next())
        return q.value("text").toString();
}

void Database::saveReadStatus(Aye *a)
{
    QSqlQuery q;
    q.prepare("UPDATE Quran SET readDate=:readDate , readCount=:readCount WHERE Chapter=:sore AND Verse=:aye;");

    q.bindValue(":readDate",a->getReadDate());
    q.bindValue(":readCount",a->getReadCount());
    q.bindValue(":sore",a->getChapter());
    q.bindValue(":aye",a->getVerse());

    qDebug()<<q.exec();


}




