#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);

    contact.setUrl("http://www.al-abyad.ir/contact");
    guide.setUrl("http://www.al-abyad.ir/support");
    site.setUrl("http://www.al-abyad.ir");
}

Help::~Help()
{
    delete ui;
}

void Help::setWidgetText()
{
    ui->tabWidget->setTabText(0,Language::translate("about"));
    ui->tabWidget->setTabText(1,Language::translate("shortcutGuide"));

    ui->pushButton_contact->setText(Language::translate("contactUs"));
    ui->pushButton_site->setText(Language::translate("visitSite"));
    ui->pushButton_guide->setText(Language::translate("userGuide"));

    this->setWindowTitle(Language::translate("help"));
}



void Help::on_pushButton_contact_clicked()
{
    QDesktopServices::openUrl(contact);
}

void Help::on_pushButton_guide_clicked()
{
    QDesktopServices::openUrl(guide);
}

void Help::on_pushButton_site_clicked()
{
    QDesktopServices::openUrl(site);
}
