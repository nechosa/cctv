#ifndef PARAM_H
#define PARAM_H

#include <QDialog>
#include <QSqlTableModel>
#include <QAbstractItemModel>


/*
Класс параметров видеообьекта
Здесь будет храниться информация о видеообьекте
путь потока(URL://rtsp:192.168.0.1:8554/stream1) или файла (D:\video.avi)
Параметры записи (кодек,формат и т.д. )
*/

namespace Ui {
class Param;
}

class Param : public QDialog
{
    Q_OBJECT

public:
    explicit Param(QString path,QWidget *parent = 0);
    void sendSignal(QString path)
    {
        emit datasent(path);
    }
/*
    void sendSignal()
    {
        emit sendString("Information");
    }

signals:
      void sendString(const QString&);
*/
    ~Param();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBrowse_clicked();
    void on_pushButton_clicked();
    void on_tabWidget_selected(const QString &arg1);
   // void on_tabWidget_currentChanged(QWidget *arg1);
    void on_tabWidget_currentChanged(int index);
    void on_play_clicked();
    void on_tableView_clicked(const QModelIndex &index);

public slots:
    int intaudio();
    int intvideo();
    int intmux();
    void setUrl(QString mypath);
public slots:
// функция подключения к базе данных
    void connectToSql();

private:
    Ui::Param *ui;
    int audioCodec;
    int videoCodec;
    int format;
    QString streampath;
    // таймер для функции подключения
    QTimer *timer;
    // модель данных
    QSqlTableModel *model;
    // подключение к базе данных
    QSqlDatabase db;


private:
    int audio;
    int mux ;
    int video;

signals:
    void datasent(const QString);
};

#endif // PARAM_H
