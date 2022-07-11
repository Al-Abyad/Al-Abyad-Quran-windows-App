#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T09:46:07
#
#-------------------------------------------------

QT       += core gui sql multimedia xml network winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Abyaz
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    aye.cpp \
    ayecordinate.cpp \
    sore.cpp \
    ayepixitem.cpp \
    scenepage.cpp \
    page.cpp \
    audio.cpp \
    language.cpp \
    downloader.cpp \
    index.cpp \
    customgraphicview.cpp \
    bookmark.cpp \
    bookmarkinfo.cpp \
    customslider.cpp \
    qary.cpp \
    downloadinfo.cpp \
    downloadinfoquran.cpp \
    setting.cpp \
    global.cpp \
    thread.cpp \
    downloadcontrol.cpp \
    register.cpp \
    customdock.cpp \
    addread.cpp \
    examlabel.cpp \
    persiandate.cpp \
    soredialog.cpp \
    translation.cpp \
    help.cpp

HEADERS  += mainwindow.h \
    database.h \
    aye.h \
    ayecordinate.h \
    sore.h \
    ayepixitem.h \
    scenepage.h \
    page.h \
    audio.h \
    language.h \
    downloader.h \
    index.h \
    customgraphicview.h \
    bookmark.h \
    bookmarkinfo.h \
    customslider.h \
    qary.h \
    downloadinfo.h \
    downloadinfoquran.h \
    setting.h \
    global.h \
    thread.h \
    downloadcontrol.h \
    register.h \
    customdock.h \
    addread.h \
    examlabel.h \
    persiandate.h \
    soredialog.h \
    translation.h \
    help.h

FORMS    += mainwindow.ui \
    setting.ui \
    downloadcontrol.ui \
    register.ui \
    addread.ui \
    soredialog.ui \
    help.ui

RESOURCES += \
    resources.qrc

win32{
RC_FILE=abyaz.rc
}


