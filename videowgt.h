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
    explicit VideoWgt(QString Title,QWidget *parent = 0);

    void incCount();//увеличение счетчика принятого пакета
    int getCount();// получение значения счетчика
    void decCount();//уменьшение счетчика
    void setPath(QString newpath);
    void setvisibleControlButtons();
    bool getvisibleControlButtons();
    // void setCount();//установка счетчика

    ~VideoWgt();
   //  virtual void mouseDoubleClickEvent(QMouseEvent *pe);
     void enterEvent(QEvent *);
     void leaveEvent(QEvent *);
     void setNumber(int n);
     int key;
     void virtual keyPressEvent(QKeyEvent *event)
     {
         key = event->key();
     }
     void virtual keyReleaseEvent(QKeyEvent *event){
      if(event->key()!=key)
      {
          return;
      }
      key = 0;
      switch (event->key()) {
      case Qt::Key_S:
          this->setVisibleButtons();

                break;
            default:
                break;
            }
        }
private:
    Ui::VideoWgt *ui;
    VlcInstance *_instance;
    VlcMedia *_media;
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

signals:
       void sigClose();
       void doubleClick();
       void maxWindow();
protected:
      virtual void closeEvent(QCloseEvent *event);
       bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void processFrameAndUpdateGui();
/*
private:
    cv::Mat mat;
    cv::VideoCapture capture;
    */

};


#endif // VIDEOWGT_H
