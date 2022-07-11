#include "addread.h"
#include "ui_addread.h"

AddRead::AddRead(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRead)
{
    ui->setupUi(this);

    setComboItem();
}

AddRead::~AddRead()
{
    delete ui;
}

void AddRead::show()
{
    QDialog::show();
    setComboItem();
}

void AddRead::setTextWidgets()
{
    this->setWindowTitle(Language::translate(""));
    ui->labelpageFrom->setText(Language::translate("from"));
    ui->label_pageTo->setText(Language::translate("to"));
    ui->label_time->setText(Language::translate("time"));

    setWidgets();
}

void AddRead::on_buttonBox_accepted()
{
    emit pageRead(ui->spinBox_pageFrom->value(),ui->spinBox_pageTo->value(),ui->comboBox->currentIndex());
}

void AddRead::setComboItem()
{
    ui->comboBox->clear();
    ui->comboBox->addItem(Language::translate("today"));
    ui->comboBox->addItem(Language::translate("yesterday"));

    for(int i=2;i<=40;i++)
        ui->comboBox->addItem(QString::number(i)+Language::translate("days")+Language::translate("ago"));
}

void AddRead::setWidgets()
{
    ui->horizontalLayout->removeWidget(ui->labelpageFrom);
    ui->horizontalLayout->removeWidget(ui->label_time);
    ui->horizontalLayout->removeWidget(ui->label_pageTo);

    ui->horizontalLayout->removeWidget(ui->comboBox);
    ui->horizontalLayout->removeWidget(ui->spinBox_pageFrom);
    ui->horizontalLayout->removeWidget(ui->spinBox_pageTo);

    if(Language::getDirection()==Qt::RightToLeft){
        ui->horizontalLayout->addWidget(ui->labelpageFrom);
        ui->horizontalLayout->addWidget(ui->spinBox_pageFrom);

        ui->horizontalLayout->addWidget(ui->label_pageTo);
        ui->horizontalLayout->addWidget(ui->spinBox_pageTo);

        ui->horizontalLayout->addWidget(ui->label_time);
        ui->horizontalLayout->addWidget(ui->comboBox);
    }
    else if(Language::getDirection()==Qt::LeftToRight){
        ui->horizontalLayout->addWidget(ui->comboBox);
        ui->horizontalLayout->addWidget(ui->label_time);

        ui->horizontalLayout->addWidget(ui->spinBox_pageTo);
        ui->horizontalLayout->addWidget(ui->label_pageTo);

        ui->horizontalLayout->addWidget(ui->spinBox_pageFrom);
        ui->horizontalLayout->addWidget(ui->labelpageFrom);
    }

}
