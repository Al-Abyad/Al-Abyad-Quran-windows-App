#include "soredialog.h"
#include "ui_soredialog.h"

SoreDialog::SoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoreDialog)
{
    ui->setupUi(this);
    currentSore=NULL;

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
}

SoreDialog::~SoreDialog()
{
    delete ui;
}

void SoreDialog::setSore(Sore *s)
{
    if(currentSore==NULL && s!=NULL){
        currentSore=s;
        ui->tabWidget->setTabText(0,Language::translate("sore")+" "+s->getName());
        ui->tabWidget->setTabText(1,Language::translate("fazlSore")+" "+s->getName());//فضیلت و خواص سوره
        ui->tabWidget->setTabText(2,Language::translate("barekatSore")+" "+s->getName());//آثار و برکات سوره

        //ui->plainTextEdit_fazl->
        ui->textEdit_fazl->setText(s->getFazl());
        ui->textEdit_barekat->setText(s->getBarekat());
        ui->textEdit_trans->setText(s->getTrans());
        showTable();
    }
    else if(currentSore!=NULL && currentSore->getNumber()!=s->getNumber()){
        currentSore=s;
        ui->tabWidget->setTabText(0,Language::translate("sore")+" "+s->getName());
        ui->tabWidget->setTabText(1,Language::translate("fazlSore")+" "+s->getName());//فضیلت و خواص سوره
        ui->tabWidget->setTabText(2,Language::translate("barekatSore")+" "+s->getName());//آثار و برکات سوره

        //ui->plainTextEdit_fazl->
        ui->textEdit_fazl->setText(s->getFazl());
        ui->textEdit_barekat->setText(s->getBarekat());
        ui->textEdit_trans->setText(s->getTrans());

        showTable();
    }
    setWidgetText();
}

void SoreDialog::setWidgetText()
{

    if(currentSore!=NULL){

        if(QString::compare(Language::getCurrentLanguage(),"persian")==0 || QString::compare(Language::getCurrentLanguage(),"arabic")==0){
            ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tab_trans));



            //ui->tabWidget->setTabText(0,Language::translate("sore")+" "+currentSore->getName());

            if(ui->tabWidget->indexOf(ui->tab_fazl)==-1){
                ui->tabWidget->setTabText(0,Language::translate("sore")+" "+currentSore->getName());
                ui->tabWidget->insertTab(1,ui->tab_fazl,Language::translate("fazlSore")+" "+currentSore->getName());
                ui->tabWidget->insertTab(2,ui->tab_barekat,Language::translate("barekatSore")+" "+currentSore->getName());
            }

        }
        else{
            ui->tabWidget->setTabText(0,Language::translate("sore")+" "+currentSore->getEnName());
            ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tab_fazl));
            ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tab_barekat));

            //ui->tabWidget->setTabText(0,Language::translate("sore")+" "+currentSore->getEnName());

            if(ui->tabWidget->indexOf(ui->tab_trans)==-1)
                ui->tabWidget->insertTab(1,ui->tab_trans,"Transliteration");
        }
        this->setWindowTitle(Language::translate("soreInfo"));

        showTable();
    }


}

void SoreDialog::showTable()
{
    if(currentSore!=NULL){
        ui->tableWidget->clear();

        ui->tableWidget->setColumnCount(4);
        QTableWidgetItem *item1=new QTableWidgetItem;
        QTableWidgetItem *item2=new QTableWidgetItem;
        QTableWidgetItem *item3=new QTableWidgetItem;
        QTableWidgetItem *item4=new QTableWidgetItem;

        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);

        item1->setText(Language::translate("name"));
        item2->setText(Language::translate("numAye"));
        item3->setText(Language::translate("nozol"));
        item4->setText(Language::translate("locNozol"));

        ui->tableWidget->setHorizontalHeaderItem(0,item1);
        ui->tableWidget->setHorizontalHeaderItem(1,item2);
        ui->tableWidget->setHorizontalHeaderItem(2,item3);
        ui->tableWidget->setHorizontalHeaderItem(3,item4);


        QTableWidgetItem *item1_1=new QTableWidgetItem;
        QTableWidgetItem *item2_2=new QTableWidgetItem;
        QTableWidgetItem *item3_3=new QTableWidgetItem;
        QTableWidgetItem *item4_4=new QTableWidgetItem;

        item1_1->setTextAlignment(Qt::AlignCenter);
        item2_2->setTextAlignment(Qt::AlignCenter);
        item3_3->setTextAlignment(Qt::AlignCenter);
        item4_4->setTextAlignment(Qt::AlignCenter);

        item1_1->setText(currentSore->getName());
        item2_2->setText(QString::number(currentSore->getVerse()));
        item3_3->setText(currentSore->getTartibNozol());
        item4_4->setText(Language::translate(currentSore->getLocNozol()));//makki or madani


        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setRowCount(1);

        ui->tableWidget->setItem(0,0,item1_1);
        ui->tableWidget->setItem(0,1,item2_2);
        ui->tableWidget->setItem(0,2,item3_3);
        ui->tableWidget->setItem(0,3,item4_4);
    }


}
