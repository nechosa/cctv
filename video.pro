#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T08:57:46
#
# Программа "Система видеонаблюдения"
# Автор: Нечёса И.А.
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = video
TEMPLATE = app


SOURCES += main.cpp\
        videowgt.cpp \
    window.cpp \
    param.cpp \
    databaseconf.cpp \
    udpclient.cpp \
    connectsettingsdb.cpp

HEADERS  += videowgt.h \    window.h \
    param.h \
    databaseconf.h \
    udpclient.h \
    connectsettingsdb.h

FORMS    += videowgt.ui \
    window.ui \
    param.ui \
    databaseconf.ui \
    udpclient.ui \
    connectsettingsdb.ui

 win32 {
INCLUDEPATH +=../vlc/include/

INCLUDEPATH +=../../vlc/include/
LIBS += -L../../vlc/lib -lvlc-qt-widgets
LIBS += -L../../vlc/lib  -lvlc-qt
LIBS += -L../../icu/lib  -licuin
}
unix{
    LIBS        += -lvlc-qt -lvlc-qt-widgets
}


#INCLUDEPATH+=D:\\opencv\\opencv249\\opencv\\build\\include
#INCLUDEPATH+=D:\\opencv\\opencv249\\opencv\\build\\include\\opencv


#LIBS += -LD:\opencv\opencv249\opencv\build\x86\vc10\lib\ \
#-lopencv_core249d \
#-lopencv_contrib249d \
#-lopencv_features2d249d \
#-lopencv_flann249d \
#-lopencv_highgui249d \
#-lopencv_objdetect249d \
#-lopencv_video249d \
#-lopencv_legacy249d \
#-lopencv_calib3d249d \
#-lopencv_ml249d \
#-lopencv_imgproc249d



RESOURCES += \
    resourses.qrc
RC_FILE = myicon.rc






