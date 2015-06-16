#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "databaseconf.h"
#include "const.h"
#include "udpclient.h"
#include <QMouseEvent>
#include "videowgt.h"
#include <QList>
#include <QDesktopWidget>
#include <QVector>
#include <QProcess>
#include <QSettings>
#include <QLayout>

/*
Класс для отображения и компоновки главной формы
*/

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

private:
    int layout_type;
    int fullscr;
    void initSettings();
    void initScreen();
    bool lay;
    void showPanel();
    void setLayoutType(int layout);
    int getLayoutType();
    QGridLayout* pgrdLayout6;
    QGridLayout* pgrdLayout4;
    QGridLayout* pgrdLayout3;
    QString m_sSettingsFile;
    int worktable;
     bool panel;


    
public:

    explicit Window(QWidget *parent = 0);
    ~Window();
    QVector <VideoWgt *> w;//обьекты видеоизображений
    QRect screen;
    int key1;

    void virtual keyPressEvent(QKeyEvent *event);
    void virtual keyReleaseEvent(QKeyEvent *event);
    void help();
    void saveSettings();
    void loadSettings();

private slots:

    void play_in_Window(QString path,unsigned int operStatus);

    void showOn_MaxMin();
    void moveScreen(bool change = true);

    void showLayout();
    void showClient();
    void showBase();

    void layoutx(int num);
    void layoutx_h(int num);
    void layoutx_v(int num);

    void layout2_h();
    void layout2_v();
    void layout3_h();
    void layout3_v();
    void layout4_h();
    void layout4_v();
    void layout4();
    void layout6();

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
