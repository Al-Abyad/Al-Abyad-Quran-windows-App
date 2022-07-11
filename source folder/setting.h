#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QFileDialog>
#include <QSettings>
#include "qary.h"
#include "language.h"
#include "global.h"

#include <QLibrary>

#include <QDebug>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();

    bool settingExist();
    void saveSetting(QString key,QVariant value);
    QVariant loadSetting(QString key);
    void show();
    void setQary(QList<Qary*> *q);



private:
    Ui::Setting *ui;
    QSettings *setting;
    int currentQary;
    QString langSetting;
    Global::DownloadState dwnState;
    QList<Qary*> *qary;
    QList<Qary*> *allQary;


    QPushButton *chooseFolder_add,*addQary_add;
    QLineEdit *lineEdt_qaryName_add,*lineEdt_folder_add;
    QLabel *lbl_qaryName_add;

    QPushButton *chooseFolder_edit,*editQary_edit,*buttonDeleteQary_edit;

    QLineEdit *lineEdt_qaryName_edit,*lineEdt_folder_edit;

    QLabel *lbl_qaryName_edit;
    QComboBox *qaryCombo_edit;


    void setUI();
    void setLangComboItem();
    void setQaryComboItem();
    void setDefult();
    void setSetting();

private slots:
    void showDialogFile_edit();
    void showDialogFile_add();

    void addQary();
    void editQary();
    void deleteQary();
    void setCurrentQary(int i);

    void on_radioButton_dwnSore_clicked(bool checked);

    void on_radioButton_dwnPage_clicked(bool checked);

    void on_radioButton_dwnDeactive_clicked(bool checked);

    void on_radioButton_dwnAye_clicked(bool checked);

    void on_buttonBox_accepted();

    void on_comboBox_lang_currentTextChanged(const QString &arg1);


    void on_pushButton_reset_clicked();

public slots:
    void setTextWidgets();

signals:
    void downloadSetting(Global::DownloadState);
    void languageSetting(QString);
    void addQarySetting(Qary*);
    void editQarySetting(Qary*);
    void deleteQarySetting(Qary*);
    void settingsSaves();
    void resetDocks();//when docks floated and we can't access them

};

#endif // SETTING_H
