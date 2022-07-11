
#include "ui_setting.h"
#include "setting.h"



Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);


    setting=new QSettings(QCoreApplication::organizationName(),QCoreApplication::applicationName(),this);
    setting->setObjectName(QCoreApplication::applicationName());


    addQary_add=new QPushButton("add",this);
    chooseFolder_add=new QPushButton("choosefolder",this);
    lineEdt_folder_add=new QLineEdit(this);
    lineEdt_qaryName_add=new QLineEdit(this);
    lbl_qaryName_add=new QLabel("name",this);

    editQary_edit=new QPushButton("edit",this);
    buttonDeleteQary_edit=new QPushButton("delete",this);
    chooseFolder_edit=new QPushButton("choosefolder",this);
    lineEdt_folder_edit=new QLineEdit(this);
    lineEdt_qaryName_edit=new QLineEdit(this);
    lbl_qaryName_edit=new QLabel("name",this);
    qaryCombo_edit=new QComboBox(this);

    setLangComboItem();

    connect(chooseFolder_add,SIGNAL(clicked(bool)),this,SLOT(showDialogFile_add()));
    connect(chooseFolder_edit,SIGNAL(clicked(bool)),this,SLOT(showDialogFile_edit()));
    connect(addQary_add,SIGNAL(clicked(bool)),this,SLOT(addQary()));
    connect(editQary_edit,SIGNAL(clicked(bool)),this,SLOT(editQary()));
    connect(buttonDeleteQary_edit,SIGNAL(clicked(bool)),this,SLOT(deleteQary()));
    connect(qaryCombo_edit,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentQary(int)));



}

Setting::~Setting()
{
    delete ui;
}

void Setting::show(){
    QDialog::show();

    if(settingExist())
        setSetting();
    else
        setDefult();
    setUI();

}
void Setting::setDefult()
{
    ui->radioButton_dwnAye->setChecked(true);
    ui->comboBox_lang->setCurrentText("persian");

}

void Setting::setSetting()
{
    Global::DownloadState dwn=static_cast<Global::DownloadState>(setting->value("downloadState").toUInt());
    if(dwn==Global::DownloadAye)
        ui->radioButton_dwnAye->setChecked(true);
    if(dwn==Global::DownloadPage)
        ui->radioButton_dwnPage->setChecked(true);
    if(dwn==Global::DownloadSore)
        ui->radioButton_dwnSore->setChecked(true);
    if(dwn==Global::downloadOff)
        ui->radioButton_dwnDeactive->setChecked(true);

    ui->comboBox_lang->setCurrentText(Language::getCurrentLanguage());
}

bool Setting::settingExist()
{

    if(setting->value("apprun").toInt()==1)
        return true;
    return false;
}

void Setting::saveSetting(QString key, QVariant value)
{


    qDebug()<<"app "<<setting->value("apprun").toInt();
    setting->setValue(key,value);
}

QVariant Setting::loadSetting(QString key)
{
    return setting->value(key);
}

void Setting::setQary(QList<Qary *> *q)
{
    allQary=q;

    setQaryComboItem();
}



void Setting::setUI()
{

    if(Language::getDirection()==Qt::RightToLeft){
        ui->gridLayout_add_qary->addWidget(lbl_qaryName_add,0,1);
        ui->gridLayout_add_qary->addWidget(lineEdt_qaryName_add,0,0);

        ui->gridLayout_add_qary->addWidget(chooseFolder_add,1,1);

        lineEdt_folder_add->setEnabled(false);
        ui->gridLayout_add_qary->addWidget(lineEdt_folder_add,1,0);

        ui->gridLayout_add_qary->addWidget(addQary_add,2,1);


        ui->gridLayout_edit_qary->addWidget(qaryCombo_edit,0,1);

        ui->gridLayout_edit_qary->addWidget(lbl_qaryName_edit,1,0);
        ui->gridLayout_edit_qary->addWidget(lineEdt_qaryName_edit,1,1);

        ui->gridLayout_edit_qary->addWidget(chooseFolder_edit,2,0);

        lineEdt_folder_edit->setEnabled(false);
        ui->gridLayout_edit_qary->addWidget(lineEdt_folder_edit,2,1);

        ui->gridLayout_edit_qary->addWidget(editQary_edit,3,1);
        ui->gridLayout_edit_qary->addWidget(buttonDeleteQary_edit,3,0);


        ui->groupBox_download->setAlignment(Qt::AlignRight);
        ui->groupBox_qaryAdd->setAlignment(Qt::AlignRight);
        ui->groupBox_qary->setAlignment(Qt::AlignRight);

    }
    else if(Language::getDirection()==Qt::LeftToRight){
        ui->gridLayout_add_qary->addWidget(lbl_qaryName_add,0,0);
        ui->gridLayout_add_qary->addWidget(lineEdt_qaryName_add,0,1);

        ui->gridLayout_add_qary->addWidget(chooseFolder_add,1,0);

        lineEdt_folder_add->setEnabled(false);
        ui->gridLayout_add_qary->addWidget(lineEdt_folder_add,1,1);

        ui->gridLayout_add_qary->addWidget(addQary_add,2,0);


        ui->gridLayout_edit_qary->addWidget(qaryCombo_edit,0,0);

        ui->gridLayout_edit_qary->addWidget(lbl_qaryName_edit,1,1);
        ui->gridLayout_edit_qary->addWidget(lineEdt_qaryName_edit,1,0);

        ui->gridLayout_edit_qary->addWidget(chooseFolder_edit,2,1);

        lineEdt_folder_edit->setEnabled(false);
        ui->gridLayout_edit_qary->addWidget(lineEdt_folder_edit,2,0);

        ui->gridLayout_edit_qary->addWidget(editQary_edit,3,0);
        ui->gridLayout_edit_qary->addWidget(buttonDeleteQary_edit,3,1);


        ui->groupBox_download->setAlignment(Qt::AlignLeft);
        ui->groupBox_qaryAdd->setAlignment(Qt::AlignLeft);
        ui->groupBox_qary->setAlignment(Qt::AlignLeft);

}

}

void Setting::setLangComboItem()
{
    ui->comboBox_lang->addItems(QStringList(Language::getLanguges()));
}

void Setting::setQaryComboItem()
{
    qaryCombo_edit->clear();
    for(int i=0;i<allQary->count();i++){
        if(QString::compare(allQary->at(i)->getType(),"dir")==0)
            qaryCombo_edit->addItem(allQary->at(i)->getName(),i);
    }
    qaryCombo_edit->setCurrentIndex(0);
}



void Setting::showDialogFile_edit()
{
    QFileDialog d;
    d.setFileMode(QFileDialog::Directory);
    d.setOption(QFileDialog::ShowDirsOnly);
    lineEdt_folder_edit->setText(d.getExistingDirectory());
}

void Setting::showDialogFile_add()
{
    QFileDialog d;
    d.setFileMode(QFileDialog::Directory);
    d.setOption(QFileDialog::ShowDirsOnly);
    lineEdt_folder_add->setText(d.getExistingDirectory());
}

void Setting::setCurrentQary(int i)
{
    if(qaryCombo_edit->count()>0){
        currentQary=qaryCombo_edit->itemData(i).toInt();
        lineEdt_qaryName_edit->setText(allQary->at(currentQary)->getName());
        lineEdt_folder_edit->setText(allQary->at(currentQary)->getDir());
    }
    else{
        lineEdt_qaryName_edit->clear();
        lineEdt_folder_edit->clear();
    }
}

void Setting::addQary()
{
    if(lineEdt_qaryName_add->text().isEmpty()){
        lineEdt_qaryName_add->setPlaceholderText(Language::translate("enterName"));
    }
    else if(lineEdt_folder_add->text().isEmpty()){
        lineEdt_folder_add->setPlaceholderText(Language::translate("chooseFolder"));
    }
    else if(lineEdt_folder_add->text().isEmpty() && lineEdt_qaryName_add->text().isEmpty()){
        lineEdt_qaryName_add->setPlaceholderText(Language::translate("enterName"));
        lineEdt_folder_add->setPlaceholderText(Language::translate("chooseFolder"));
    }
    else{
        Qary *q=new Qary();
        q->setName(lineEdt_qaryName_add->text());
        q->setDir(lineEdt_folder_add->text());
        q->setType("dir");

        allQary->append(q);

        setQaryComboItem();
        emit addQarySetting(q);
    }

}

void Setting::editQary()
{
    if(qaryCombo_edit->count()>0){
        if(lineEdt_qaryName_edit->text().isEmpty()){
            lineEdt_qaryName_edit->setPlaceholderText(Language::translate("enterName"));
        }
        else if(lineEdt_folder_edit->text().isEmpty()){
            lineEdt_folder_edit->setPlaceholderText(Language::translate("chooseFolder"));
        }
        else if(lineEdt_folder_edit->text().isEmpty() && lineEdt_qaryName_edit->text().isEmpty()){
            lineEdt_qaryName_edit->setPlaceholderText(Language::translate("enterName"));
            lineEdt_folder_edit->setPlaceholderText(Language::translate("chooseFolder"));
        }
        else{
            Qary *q=allQary->at(currentQary);

            q->setName(lineEdt_qaryName_edit->text());
            q->setDir(lineEdt_folder_edit->text());

            setQaryComboItem();
            emit editQarySetting(q);
        }
    }

}

void Setting::deleteQary()
{
    if(qaryCombo_edit->count()>0){
        Qary *q=allQary->at(currentQary);

        allQary->removeAt(currentQary);

        setQaryComboItem();
        emit deleteQarySetting(q);
    }
}





void Setting::on_radioButton_dwnSore_clicked(bool checked)
{
    if(checked)
        dwnState=Global::DownloadSore;
}

void Setting::on_radioButton_dwnPage_clicked(bool checked)
{
    if(checked)
        dwnState=Global::DownloadPage;
}

void Setting::on_radioButton_dwnDeactive_clicked(bool checked)
{
    if(checked)
        dwnState=Global::downloadOff;
}

void Setting::on_radioButton_dwnAye_clicked(bool checked)
{
    if(checked)
        dwnState=Global::DownloadAye;
}

void Setting::on_buttonBox_accepted()
{
    emit downloadSetting(dwnState);
    emit languageSetting(langSetting);
    emit settingsSaves();
}



void Setting::on_comboBox_lang_currentTextChanged(const QString &arg1)
{
    langSetting=arg1;
}

void Setting::setTextWidgets()
{
    this->setWindowTitle(Language::translate("setting"));

    ui->groupBox_lang->setTitle(Language::translate("language"));
    ui->groupBox_download->setTitle(Language::translate("download"));
    ui->groupBox_qary->setTitle(Language::translate("qary"));
    ui->groupBox_qaryAdd->setTitle(Language::translate("addQary"));
    ui->groupBox_qaryEdit->setTitle(Language::translate("editQary"));

    ui->radioButton_dwnAye->setText(Language::translate("dwnAye"));
    ui->radioButton_dwnDeactive->setText(Language::translate("dwnDeactive"));
    ui->radioButton_dwnPage->setText(Language::translate("dwnPage"));
    ui->radioButton_dwnSore->setText(Language::translate("dwnSore"));


    addQary_add->setText(Language::translate("add"));
    chooseFolder_add->setText(Language::translate("chooseFolder"));
    lbl_qaryName_add->setText(Language::translate("name"));

    editQary_edit->setText(Language::translate("edit"));
    chooseFolder_edit->setText(Language::translate("chooseFolder"));
    lbl_qaryName_edit->setText(Language::translate("name"));
    buttonDeleteQary_edit->setText(Language::translate("delete"));


    setUI();

}

void Setting::on_pushButton_reset_clicked()
{
    ui->radioButton_dwnAye->setChecked(true);
    ui->comboBox_lang->setCurrentText("persian");

    emit downloadSetting(Global::DownloadAye);
    emit languageSetting("persian");
    emit resetDocks();

}
