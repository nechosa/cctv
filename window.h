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
    int fullscr;
    int worktable;
    QString m_sSettingsFile;
    void initSettings();

    
public:

    explicit Window(QWidget *parent = 0);
    ~Window();
    VideoWgt *w[6];//обьекты видеоизображений
    QRect screen;
    int key1;

    void virtual keyPressEvent(QKeyEvent *event);
    void virtual keyReleaseEvent(QKeyEvent *event);
    void help();
    void saveSettings();
    void loadSettings();

private slots:

    void play_in_Window(QString path,unsigned int operStatus);
    void on_but_3_clicked();
    void showOn_MaxMin();
    void moveScreen(bool change = true);
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
