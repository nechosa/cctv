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

win32
{
#BINARY = ..
#BINARY = ../..
#DESTDIR = $$BINARY/bin(mingw)
#DESTDIR = $$BINARY/bin(msvs)
}
#system( rm $$BINARY/bin(msvs)/video.exe)

SOURCES += main.cpp\
        videowgt.cpp \
        window.cpp \
        param.cpp \
        databaseconf.cpp \
        udpclient.cpp \
        connectsettingsdb.cpp 

HEADERS  += videowgt.h \
        window.h \
        param.h \
        databaseconf.h \
        udpclient.h \
        const.h \
        version.h \
        connectsettingsdb.h 

FORMS    += videowgt.ui \
    window.ui \
    param.ui \
    databaseconf.ui \
    udpclient.ui \
    connectsettingsdb.ui 

LIBVLC = -lvlc-qt -lvlc-qt-widgets

win32
{
    #win32-msvc2010
    #{
    #   PATH_LIBVLC = ../vlc_msvs
    #}
    #else:
    #win32-g++
    #{
        PATH_LIBVLC = ../vlc_mingw
    #}
        INCLUDEPATH +=$$PATH_LIBVLC/include
        LIBS += -L$$PATH_LIBVLC/lib
}
unix{
    DEFINES = DEFAULT_SCREEN
}

 LIBS +=$$LIBVLC

RESOURCES += \
    resourses.qrc

win32 {
RC_FILE = myicon.rc

}
unix{

}
