#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T08:57:46
#
# Программа "Система отображения видеоинформации"
# Назначение - Программа предназначена для отображения
# потокового видео и локальных видеофайлов на ЭКП
# Автор: Нечёса И.А.,
# Отдел: 4372
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

win32
{
    win32-msvc2010
    {
        INCLUDEPATH +=../../vlc_0_9/include/
        LIBS += -L../../vlc_0_9/lib -lvlc-qt-widgets
        LIBS += -L../../vlc_0_9/lib  -lvlc-qt
    }
    #else:{}
    #win32-g++
    #{
    #    INCLUDEPATH +=../../vlc(0_9)/include/
    #    LIBS += -L../../vlc(0_9)/lib -lvlc-qt-widgets
    #    LIBS += -L../../vlc(0_9)/lib  -lvlc-qt
    #}
}
unix{
    LIBS        += -lvlc-qt -lvlc-qt-widgets
    DEFINES = DEFAULT_SCREEN
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

win32 {
RC_FILE = myicon.rc

}
unix{

}
