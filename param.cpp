#include "param.h"
#include "videowgt.h"
#include "ui_param.h"
#include <QFileDialog>
#include <QSqlTableModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>


/// Класс конфигурации
///
///

Param::Param(QString path,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Param)
{
    ui->setupUi(this);
    streampath = path;
    ui->comboAudio->addItems(Vlc::audioCodec());
    ui->comboMux->addItems(Vlc::mux());
    ui->comboVideo->addItems(Vlc::videoCodec());
    ui->editUrl->setText(streampath);

}

Param::~Param()
{
    qDebug()<< "close Param";
    if (db.isOpen())
      db.close();
    delete ui;
}

void Param::on_buttonBox_accepted()
{
    /*
   audio = ui->comboAudio->currentIndex();
   mux = ui->comboMux->currentIndex();
   video = ui->comboVideo->currentIndex();
   */
}

void Param::setUrl(QString mypath)
{
    ui->editUrl->setText(mypath);
}
int Param::intaudio()
{
    return  ui->comboAudio->currentIndex();
}
int Param::intvideo()
{
    return ui->comboVideo->currentIndex();
}
int Param::intmux()
{
    return ui->comboMux->currentIndex();
}

void Param::on_buttonBrowse_clicked()
{
    QString path =QFileDialog::getExistingDirectory(this, QObject::tr("Open directory"),
                                              ui->editPath->text(),
                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    ui->editPath->setText(path);
}

void Param::on_pushButton_clicked()
{
      //ui->tableView->setModel(model);
}

void Param::on_tabWidget_selected(const QString &arg1)
{
     ui->label->setText(arg1);
}

/*
void Param::on_tabWidget_currentChanged(QWidget *arg1)
{
    ui->label->setText("on_tabWidget_currentChanged");
}

*/
void Param::on_tabWidget_currentChanged(int index)
{
    if (index==1)
    {
          ui->label->setText("1345");
          if (db.isOpen())
            db.close();
    }
    if (index==2)
    {
        timer = new QTimer(this);
        // "тушим" все элементы на форме
        ui->tableView->setEnabled(false);
        // связываем таймер и функцию
        connect(timer, SIGNAL(timeout()), this, SLOT(connectToSql()));
        // обнуляем таймер
        timer->stop();
        // выводим сообщение пользователю, тег <b> означает "жирный" шрифт
        ui->label->setText("<b>Ожидайте,идет подключение к серверу...</b>");
        // запускаем таймер через 1,5 секунды
        timer->start(1500);
    }
}

void Param::connectToSql()
{
// указываем драйвер
/*
    db = QSqlDatabase::addDatabase("QODBC");
// указываем на соединение DSN
    db.setDatabaseName("mydsn");
    */

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("configuration");
    db.setUserName("elton");
    db.setHostName("epica");
    db.setPassword("password");
// если соединение установлено
    if(db.open())
    {
    // сообщение пользователю
    ui->label->setText("<b>Соединение установлено,можно работать</b>");
// активируем элементы управления
    ui->tableView->setEnabled(true);
    // объявляем модель данных
    model = new QSqlTableModel(this);
    // указываем таблицу из БД Test (смотри предыдущие уроки)
    model->setTable("configuration");
    // заносим данные в модель
    // если удачно
    if(model->select())
    {
        // передаем данные из модели в tableView
        ui->tableView->setModel(model);
        // устанавливаем высоту строки по тексту
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
        // шапка для первой колонки
        /*model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
        // шапка для второй колонки
        model->setHeaderData(1, Qt::Horizontal, tr("Возраст"));
        */
        // передача управления элементу tableView
        ui->tableView->setFocus();
     }
        // если данные не перенеслись в модель
    else
    {
        // показываем ошибку в статусе
        ui->label->setText(model->lastError().text());
    }
        // останавливаем таймер
        timer->stop();
    }
// если БД не открыта
else
{
// сообщение пользователю
ui->label->setText("Ошибка соединения: "+db.lastError().text());
// остановка таймера
timer->stop();
}
}

void Param::on_play_clicked()
{
     sendSignal(ui->url->text());

}
/*
 QString Param::sendPlay()
{
    return ui->url->text();
}
 */

void Param::on_tableView_clicked(const QModelIndex &index)
{
    //qDebug()<< "on_tableView_clicked";
    //qDebug()<<index.row();
    //qDebug()<<  ui->tableView->model()->itemData(index).values().last().toString();
    if (index.column()==2)
        ui->url->setText(ui->tableView->model()->itemData(index).values().last().toString());
     //qDebug()<< "***********************************";
   // qDebug()<<index();
}
