#ifndef VIDEOWGT_H
#define VIDEOWGT_H

#include <QWidget>
#include "param.h"
#include <QGridLayout>
#include <QMouseEvent>
#include <vlc-qt/Common.h>
#include <vlc-qt/Instance.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/Error.h>
#include <QDesktopWidget>
#include <QTimer>


/*
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
*/

/*
Класс видеообьекта
Формирует видеоизображение в виджете
*/


namespace Ui {
class VideoWgt;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
class Config;

class VideoWgt : public QWidget
{
    Q_OBJECT

public:
    int camera;
    void setCamera(int cam);
    int getCamera(void);
    explicit VideoWgt(QString Title,int camera,QWidget *parent = 0);
    QRect screen;
    QDesktopWidget *desktop ;
    void incCount();//увеличение счетчика принятого пакета
    int getCount() const;// получение значения счетчика
    void decCount();//уменьшение счетчика
    void setPath(QString newpath);
    QString getPath(void);
    void setvisibleControlButtons();
    bool getvisibleControlButtons() const;
    void setWindowScreen(int screen,QDesktopWidget * desktopWindow);
    int worktable;
    ~VideoWgt();
    // void setCount();//установка счетчика
    //  virtual void mouseDoubleClickEvent(QMouseEvent *pe);
    void setNumber(int n);
    int key;
    void virtual keyPressEvent(QKeyEvent *event)
    {
        key = event->key();
    }
private:
    Ui::VideoWgt *ui;
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcError *_error;
    VlcMediaPlayer *_player;
    Param  *par;
    QTimer *_timer;
    QString path;
    bool visibleButtons;
    int  count;
    bool visibleControlButtons;
    int number;


private slots:


    void openUrl();
    void on_onMaxWindow_clicked();
    void on_param_clicked();
    void on_record_clicked();
    void mySlot();
    void on_play_clicked();
    void on_stop_clicked();
    void on_volume_clicked();
    void on_but_volume_clicked();
    void on_video_fullscreen();
    void on_groupBox_clicked();
    void on_groupBox_clicked(bool checked);
    void on_video_clicked();

public slots:
    void play(QString path);
    void setVisibleButtons();
    void stop();
    bool isVisibleButtons();
    void setVideoWidgetTitle(QString title);
    void setVideoMax();
    void showMaxCam7();


signals:
    void formclose();
    void close();

signals:
    void sigClose();
    void doubleClick(const int);
    void maxWindow();
protected:
    bool eventFilter(QObject *obj, QEvent *event);

};


#endif // VIDEOWGT_H
