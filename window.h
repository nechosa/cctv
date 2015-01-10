#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "databaseconf.h"
//#include "server.h"
#include "udpclient.h"
#include <QMouseEvent>
#include "videowgt.h"
#include <QList>
#include <QDesktopWidget>
/*
Класс для отображения и компоновки главной формы
*/

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT
    
public:
   QDesktopWidget *desktop ;
   QRect screen;
   int worktable;
   int fullscr;
   explicit Window(QWidget *parent = 0);
   ~Window();
   VideoWgt *w0;
   QMultiMap <QString,int> map;
   int key1;
   void virtual keyPressEvent(QKeyEvent *event)
   {
       key1 = event->key();
   }
   void virtual keyReleaseEvent(QKeyEvent *event){
    if(event->key()!=key1)
    {
        return;
    }
    key1 = 0;
    switch (event->key()) {
    case Qt::Key_F5:
            showOn_MaxMin();
        break;
    case Qt::Key_S:
        w->setVisibleButtons();
        w1->setVisibleButtons();
        w2->setVisibleButtons();
        w3->setVisibleButtons();
        w4->setVisibleButtons();
        w5->setVisibleButtons();
              break;
          default:
              break;
          }
      }



private slots:

    void play_on_UdpClient(QString path);
    void play_in_Window(QString path,unsigned int operStatus);

    void on_but_3_clicked();
    //void on_but_2_clicked();
    void on_but_4_clicked();
    void showOn_MaxMin();
    void test();
    void showMaxCam(int camera);
    void showMaxCam1();
    void showMaxCam2();
    void showMaxCam3();
    void showMaxCam4();
    void showMaxCam5();
    void showMaxCam6();
   // void showMaxCam7(VideoWgt *w7);


    void on_but_5_clicked();

private:
    Ui::Window *ui;
    //класс сервера
   // Server *server;
    //класс клиента
    UdpClient *client;
    //класс для базы данных
    DatabaseConf *databases;
    //обьекты видеоизображений
    VideoWgt * w;
    VideoWgt * w1;
    VideoWgt * w2;
    VideoWgt * w3;
    VideoWgt * w4;
    VideoWgt * w5;   // Video *v;


signals:
       void showOnMax();
       void showOnMin();

       //void doubleClick();
/*
protected:
      void mouseDoubleClickEvent(QMouseEvent *pe);
      */



};

#endif // WINDOW_H
