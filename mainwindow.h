#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videowgt.h"
/*
#include "videowgt.h"

#include "server.h"
#include "databaseconf.h"
*/
#include <QSqlTableModel>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
    VideoWgt *w ;
    VideoWgt *w1;
    VideoWgt *w2;
    VideoWgt *w3;
    VideoWgt *w4;
    VideoWgt *w5;
    /*
    Server *server;
    DatabaseConf *databases;
    */
    // таймер для функции подключения
        QTimer *timer;
    // модель данных
      QSqlTableModel *model;
    // подключение к базе данных

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
       QSqlDatabase db;

private slots:
    void on_showOff_clicked();

    void on_pushButton_clicked();
     void mySlot();


     void on_dbConfig_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
