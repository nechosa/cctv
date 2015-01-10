#ifndef DATABASECONF_H
#define DATABASECONF_H

#include <QWidget>
#include <QSqlTableModel>
#include "connectsettingsdb.h"



/*
Класс конфигурации и управление с базой данных

*/

namespace Ui {
class DatabaseConf;
}

class DatabaseConf : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseConf(QWidget *parent = 0);
    ~DatabaseConf();

private slots:
    void on_connect1_clicked();

    void on_connect2_clicked();

    void on_add_clicked();

    void on_database2_clicked(const QModelIndex &index);

    void on_dell_clicked();

    void on_connect_settings_db1_clicked();

    void on_connect_settings_db2_clicked();


private:
    Ui::DatabaseConf *ui;

public slots:
    void connectToSql1();
    void connectToSql2();
    int listCam(QString ipAddr);
    /*
    void setNumber();
    void setName();
    void setUrl();
    void setOperation();
    */

private:
// таймер для функции подключения
    QTimer *timer1;
    QTimer *timer2;
// модель данных
    QSqlTableModel *model1;
// подключение к базе данных
    QSqlDatabase db1;
    QSqlTableModel *model2;
// подключение к базе данных
    QSqlDatabase db2;
    QString number;
    QString name;
    QString url;
    QString operation;
    ConnectSettingsDB *settingsdb1;
    ConnectSettingsDB *settingsdb2;
    /*
    rec.setValue("number", ui->lineEdit->text());
    rec.setValue("name", ui->lineEdit_2->text());
    // значение возраста
    rec.setValue("url", ui->lineEdit_3->text());
    rec.setValue("operation", ui->lineEdit_4->text());
    */
};

#endif // DATABASECONF_H
