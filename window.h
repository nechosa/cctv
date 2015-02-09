#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "databaseconf.h"
#include "udpclient.h"
#include <QMouseEvent>
#include "videowgt.h"
#include <QList>
#include <QDesktopWidget>
#include <QVector>
#include <QProcess>
#include <QSettings>

#define NAME_PROGRAM "Представление  видеоинформации"
#define CAMERA "Камера"
#define PATH_ICON ":/icons/vista_189.ico"

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

    explicit Window(QWidget *parent = 0);
    ~Window();
    VideoWgt *w[6];//обьекты видеоизображений
    QThread *thread[6];

    QRect screen1;
    QRect screen;
    QRect screen2;

    int worktable;
    int fullscr;

    int key1;

    void setSceens();
    void setSceen1( QDesktopWidget *desktop);
    void setSceen2( QDesktopWidget *desktop);

    void virtual keyPressEvent(QKeyEvent *event);
    void virtual keyReleaseEvent(QKeyEvent *event);


    void help();
    void saveSettings();
    void loadSettings();




private slots:

    void play_in_Window(QString path,unsigned int operStatus);
    void on_but_3_clicked();
    void showOn_MaxMin();
    void on_but_5_clicked();
    void on_param_clicked();

public slots:
    void showMaxCam(int);

private:
    Ui::Window *ui;
    UdpClient *client; //класс клиента
    DatabaseConf *databases; //класс для базы данных
    QProcess *v_process;
    QSettings *settings;

signals:
    void showOnMax();
    void showOnMin();


};

#endif // WINDOW_H
