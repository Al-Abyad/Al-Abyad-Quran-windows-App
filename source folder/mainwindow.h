#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QStyleFactory>
#include <QCloseEvent>
#include <QWheelEvent>
#include <QWinTaskbarButton>
#include <QWinThumbnailToolBar>
#include <QWinThumbnailToolButton>
#include <QColorDialog>
#include <QComboBox>
#include <QLabel>
#include <QString>
#include <QScrollBar>
#include <QFile>
#include <QDir>
#include <QShortcut>
#include <QDate>
#include <QClipboard>
#include <cstdlib>
#include <ctime>
#include "page.h"
#include "database.h"
#include "sore.h"
#include "aye.h"
#include "ayecordinate.h"
#include "scenepage.h"
#include "bookmarkinfo.h"
#include "audio.h"
#include "downloader.h"
#include "downloadinfo.h"
#include "downloadinfoquran.h"
#include "language.h"
#include "setting.h"
#include "global.h"
#include "downloadcontrol.h"
#include "thread.h"
#include "addread.h"
#include "persiandate.h"
#include "translation.h"
#include "soredialog.h"
#include "help.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void show();
    QMainWindow* getCentralWindow();

private slots:

    void saveSetting();
    void setComboTrans_trans(QString l);
    void setComboTransSearch(QString l);
    void setComboTransBookmark(QString l);
    void setCurrentTranslation(QString s);
    void setSizeTrans(QString s);
    void choosetransColor();
    void handleDownloadReport(QString s);
    void handlePageCombo(const int index);
    void handleSoreCombo(const int index);
    void handleAyeCombo(const int index);
    void handleJuzCombo(const int index);
    void handleQaryCombo(const int index);
    void handleAddQary(Qary* q);
    void handleEditQary(Qary *q);
    void handleDeleteQary(Qary* q);
    void handleLanguageSetting(QString l);
    void handleDurationPlayer(int d);
    void playSound();
    void stopedSound();
    void endSoundHandle();
    void handlePlayerPosition(int v);
    void handleChangeValueMainSlider(int v);
    void handleDownloadedFile(DownloadInfo *d);
    void setDownloadState(Global::DownloadState s);

    void bookmarkHandle(int sore,int aye,QString color);//for bookmark and read date too

    void playBookmark(Aye *a);

    void itemsClickHandle(Aye *a);//for double click bookmark and click index & search

    void nextSore();
    void nextPage();
    void nextAye();
    void preSore();
    void prePage(int ayePage);
    void prePage();
    void preAye();
    void nextJuz();
    void preJuz();
    void nextQary();
    void preQary();
    void zoomPlus();
    void zoomMinus();
    void clapsToolbar();
    //void on_pushButton_nextpage_clicked();
    //void on_pushButton_previouspage_clicked();
    void clickedAye(const int sore,const int ayeSore);
    void handleAyeRead(int pageFrom,int pageTo,int difference);


    void on_pushButton_playStop_clicked();



    void on_horizontalSlider_Main_sliderMoved(int position);

    void on_pushButton_pausePlay_clicked();


    void on_btn_setting_triggered();

    void on_toolButton_download_clicked();



    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_search_index_textChanged(const QString &arg1);

    void on_pushButton_export_search_clicked();
    void on_pushButton_export_book_clicked();

    void on_checkBox_langTrans_search_clicked(bool checked);

    //void on_toolButton_aye_next_clicked();

    void on_toolButton_forward_clicked();

    void on_toolButton_backward_clicked();

    //void on_toolButton_pre_aye_clicked();

    void on_pushButton_zoom_plus_clicked();

    void on_pushButton_zoom_minus_clicked();

    void on_btn_claps_triggered();

    void on_btn_index_triggered(bool checked);

    void on_btn_translate_triggered(bool checked);

    void on_btn_search_triggered(bool checked);

    void on_btn_bookmark_triggered(bool checked);



    void on_checkBox_langTrans_book_clicked(bool checked);





    void on_comboBox_filter_index_currentTextChanged(const QString &arg1);



    void on_pushButton_hidden_clicked();


    void activeFullScreenShortcut();
    void activeTenNextPageShortcut();
    void activeTenPrevPageShortcut();



    void on_btn_fullscreen_triggered();



    void on_pushButton_pageRepeat_clicked(bool checked);

    void on_pushButton_infinityRepeat_clicked(bool checked);

    void on_pushButton_limitRepeat_clicked(bool checked);

    void on_spinBox_numRpeatAye_valueChanged(int arg1);

    void on_toolButton_volum_up_clicked();

    void on_toolButton_volum_down_clicked();

    void on_toolButton_prePage_clicked();

    void on_toolButton_nextPage_clicked();

    void on_toolButton_preSore_clicked();

    void on_toolButton_nextSore_clicked();

    void on_toolButton_preAye_clicked();

    void on_toolButton_nextAye_clicked();

    void on_toolButton_readDate_clicked();


    void on_toolButton_preJuz_clicked();

    void on_toolButton_nextJuz_clicked();

    void on_spinBox_numRpeatPage_valueChanged(int arg1);

    void on_btn_exam_triggered(bool checked);


    void on_comboBox_examSore_currentIndexChanged(int index);


    void handleDoubleClickExamLabel();

    void on_comboBox_examToAye_currentIndexChanged(int index);

    void on_comboBox_examFromAye_currentIndexChanged(int index);




    void handleFadeEnd();

    void on_radioButton_examSound_toggled(bool checked);



    void on_radioButton_examText_toggled(bool checked);

    void on_radioButton_examAye_toggled(bool checked);

    void on_radioButton_examPage_toggled(bool checked);

    void on_checkBox_examLimitPage_toggled(bool checked);

    void on_checkBox_examLimitSore_toggled(bool checked);

    void on_checkBox_examLimitAye_toggled(bool checked);



    void on_toolButton_examReset_clicked();

    void on_toolButton_examStart_clicked();

    void on_toolButton_examPlay_clicked();

    void on_toolButton_examStop_clicked();


    void on_toolButton_nozol_clicked();

    void handleResetSetting();


    void on_comboBox_examToPage_currentIndexChanged(int index);

    void on_comboBox_examFromPage_currentIndexChanged(int index);

    void on_toolButton_showAyeExam_clicked();

    void on_toolButton_preQary_clicked();

    void on_toolButton_nextQary_clicked();

    void on_btn_help_triggered();

private:
    Ui::MainWindow *ui;
    QWinTaskbarButton *taskbarbtn;
    QWinThumbnailToolBar *taskbar;
    QWinThumbnailToolButton *tskPlay, *tskNext, *tskPre, *tskPause;

    Database *db;
    QMainWindow *window;
    ScenePage *scenePage;
    Audio *player;
    Downloader *downloader;
    DownloadControl *downloadControl;
    QComboBox *pageCombo,*soreCombo,*ayeCombo,*juzCombo,*qaryCombo;
    QLabel *pageComboLabel,*soreComboLabel,*ayeComboLabel,*juzComboLabel,*qaryComboLabel;



    QComboBox *combo_trans_trans,*combo_trans_lang,*combo_trans_size;
    QLabel *label_trans_trans,*label_trans_lang,*label_trans_size;
    QPushButton *button_trans_color;
    QMap<QString,QList<Translation>* > *langTransList;
    QMap<int,QList<QString>* >* searchText;
    QMap<int,QList<QString> > currentTranslation;
    QColor translatioColor;
    QString translationFontSize;

    Setting *setting;

    QString soundPath;
    bool combosChanged;

    bool hiddenPage;

    Global::RepeatPlayerState repeatState;
    Global::PlayerState playerState;
    int numRepeat,counterRepeat;

    Global::DownloadState downloadStat;

    QMap<int,Sore*> *allQuran;
    QList<Page*> pages;
    QList<Aye*> *bookmarks;
    QList<Qary*> *qary;
    QList<Aye*> *juzList;


    int currentPage;
    int currentSore;
    int currentAye;
    int currentJuz;
    Aye *currentAyeOBJ;
    Aye *bookmarkPlaying;
    Aye *examAye;
    Qary *currentQary;

    Global::DownloadState donwloadStatus;
    Qt::LayoutDirection direction;

    AddRead *addRead;
    SoreDialog *soreDialog;
    Help *helpDialog;


    void config();
    void loadSetting();
    void setCentrMainWindow();
    void setDockToCenterMainWindow();
    void setDefultSetting();
    void setTaskbarWidgets();
    void setTranslateWidget();
    void setComboTransLangItem();
    void showTranslation();
    void setColorTrans(QColor c);
    void refereshScenePage();
    void createPages();
    void createJuzList();
    void createBookmarkList();
    void setComboSoundPanelItem();
    void setComboSore();
    void setComboAyeItem();
    void setSoundPanelDirection();
    void setComboQaryItem();
    void setComboLangSearch();
    void setComboLangBookmark();
    void setComboFilterIndex();
    void setComboFilterBookmark();

    void updateCombos();
    void setCurrentStates(Aye *a);
    void setSoreProperty();
    void setAyeReadDate();
    void downloadSound();

    void setGraphicViewScrollPoint();
    QList<DownloadInfo*> createDownloadPageList();
    QList<DownloadInfo*> createDownloadSoreList();

    Aye *isExistBookmark(int sore,int aye);

    void setPlayerSound();
    void handleCombosSoundPanel(Global::combosSignals cs, int index);

    void doAllWork();

    static void getExport(QList<Aye*> list, QString fileName,Translation trans);

    void setShortcuts();
    void setTextWidgets();

    void setReadDate(int page, int defference);




    void setExamCombos();
    void setExamAyeCombos();

    void setExamWidgets();


    Aye *pageFilterExam(int from, int to);
    QList<Aye*> getFirstAyePages(int from,int to);
    QList<Aye*> getAyePages(int from,int to);
    Aye *soreFilterExam();
    Aye *ayeFilterExam();
    Aye *allFilterExam();
    int getExamIndexAye(QList<Aye*> list,int from,int to);

    Aye* checkLimitExam();
    void performExam();


    void playExam();

    void checkExamDuration(int d);

    Global::ExamStatus checkExamAyeList();//if it returns true mean call performExam
    bool searchExam();
    void resetExam();

    const int examDurationPercent=15;
    int examAyeCount;//count of aye for perform exam  like aye filter from=1 to=4 examAyeCount=to-from+1
    QList<Aye*> *examAyeList;





protected:
    void closeEvent(QCloseEvent *e);
    void wheelEvent(QWheelEvent *event);

signals:
    void endBookmarkPlay();
};



#endif // MAINWINDOW_H
