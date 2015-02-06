#include "databaseconf.h"

#include "ui_databaseconf.h"

#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>

DatabaseConf::DatabaseConf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseConf)
{
    ui->setupUi(this);
    ui->database1->setEnabled(false);
    ui->database2->setEnabled(false);
}

DatabaseConf::~DatabaseConf()
{
        qDebug()<< "close DatabaseConf";
    delete ui;
     db1.close();
     db2.close();
}

void DatabaseConf::on_connect1_clicked()
{
    ui->connect1->setText("Переподключиться к конфигурационной базе");
    // объявляем таймер
    timer1 = new QTimer(this);
    // "тушим" все элементы на форме

    // связываем таймер и функцию
    connect(timer1, SIGNAL(timeout()), this, SLOT(connectToSql1()));
    // обнуляем таймер
    timer1->stop();
    // выводим сообщение пользователю, тег <b> означает "жирный" шрифт
    ui->label->setText("<b>Ожидайте,идет подключение к серверу...</b>");
    // запускаем таймер через 1,5 секунды
    timer1->start(1500);
}

int DatabaseConf::listCam(QString ipAddr)
{
    return 1;
}
void DatabaseConf::on_connect2_clicked()
{
    ui->connect2->setText("Переподключиться к АСУПП");
    // объявляем таймер
    timer2 = new QTimer(this);
    // "тушим" все элементы на форме

    // связываем таймер и функцию
    connect(timer2, SIGNAL(timeout()), this, SLOT(connectToSql2()));
    // обнуляем таймер
    timer2->stop();
    // выводим сообщение пользователю, тег <b> означает "жирный" шрифт
    ui->label_2->setText("<b>Ожидайте,идет подключение к серверу...</b>");
    // запускаем таймер через 1,5 секунды
    timer2->start(1500);
}

// описываем функцию подключения к БД
void DatabaseConf::connectToSql1()
{
// указываем драйвер
/*
    db = QSqlDatabase::addDatabase("QODBC");
// указываем на соединение DSN
    db.setDatabaseName("mydsn");
    */

    /*
db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("configuration");
db.setUserName("elton");
db.setHostName("epica");
db.setPassword("password");

*/
    db1 = QSqlDatabase::addDatabase("QSQLITE");
    db1.setDatabaseName("configuration");
    db1.setUserName("elton");
    db1.setHostName("epica");
    db1.setPassword("password");
// если соединение установлено
    if(db1.open())
    {
    // сообщение пользователю
    ui->label->setText("<b>Соединение установлено,можно работать</b>");
// активируем элементы управления
    ui->database1->setEnabled(true);
    // объявляем модель данных
    model1 = new QSqlTableModel(this);
    // указываем таблицу из БД Test (смотри предыдущие уроки)
    model1->setTable("configuration");
    // заносим данные в модель
    // если удачно
    if(model1->select())
    {
        // передаем данные из модели в tableView
        ui->database1->setModel(model1);
        // устанавливаем высоту строки по тексту
        ui->database1->resizeRowsToContents();
        // шапка для первой колонки
        /*model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
        // шапка для второй колонки
        model->setHeaderData(1, Qt::Horizontal, tr("Возраст"));
        */
        // передача управления элементу tableView
        ui->database1->setFocus();
     }
        // если данные не перенеслись в модель
    else
    {
        // показываем ошибку в статусе
        ui->label->setText(model1->lastError().text());
    }
        // останавливаем таймер
        timer1->stop();
    }
// если БД не открыта
else
{
// сообщение пользователю
ui->label->setText("Ошибка соединения: "+db1.lastError().text());
// остановка таймера
timer1->stop();
}
}

void DatabaseConf::connectToSql2()
{
    // указываем драйвер
    /*
        db = QSqlDatabase::addDatabase("QODBC");
    // указываем на соединение DSN
        db.setDatabaseName("mydsn");
        */

        db2 = QSqlDatabase::addDatabase("QPSQL7");
        db2.setDatabaseName("ASUPP");
        db2.setUserName("master");
        db2.setHostName("172.16.24.39");
        db2.setPassword("master");
        /*
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("configuration");
    db.setUserName("elton");
    db.setHostName("epica");
    db.setPassword("password");

*/

    // если соединение установлено
        if(db2.open())
        {
        // сообщение пользователю
        ui->label_2->setText("<b>Соединение установлено,можно работать</b>");
    // активируем элементы управления
        ui->database2->setEnabled(true);

        QSqlQueryModel* model = new QSqlQueryModel();
       // model2 = new QSqlQueryModel();
        //model1 = new QSqlTableModel(this);
        // указываем таблицу из БД Test (смотри предыдущие уроки)
/*
        model->setQuery("SELECT id_complex, name, net_address, ser_num, tech_data "
                       "FROM org_complex "
                       "WHERE id_technical_mean = (SELECT id_technical_mean FROM org_technical_mean_type WHERE name = 'Цифровая видеокамера') "
                       "ORDER BY id_complex; "
                                 );
*/

        /*
        model->setQuery("SELECT *"
                       "FROM org_complex; "
                                 );
        */



        model->setQuery("SELECT cmp.id_complex, cmp.name, cmp.net_address, cmp.ser_num, cmp.tech_data, whr.name_building, whr.num_room, whr.name_usage, whr.level "
                       "FROM org_complex cmp "
                       " LEFT JOIN "
                       "(   SELECT bld.name_building, orm.num_room, orm.name_usage, orm.level, plc.id_complex "
                       "    FROM org_place plc, org_room orm, org_building bld "
                       "    WHERE plc.id_room = orm.id_room "
                       "    AND orm.id_building = bld.id_building "
                       "    AND date_accom = (SELECT max(date_accom) FROM org_place WHERE id_complex = plc.id_complex ) "
                       ") whr "
                       "ON cmp.id_complex = whr.id_complex "
                       "WHERE id_technical_mean = (SELECT id_technical_mean FROM org_technical_mean_type WHERE name = 'Цифровая видеокамера') "
                       "ORDER BY id_complex; "
                                 );


        if( model->lastError().isValid())
        {
            qDebug() <<model->lastError();
        }
        else
        {
            qDebug() << "Всё огонь!";
        }
        ui->database2->setModel(model);
        /*
        QTableView *view = new QTableView;
        view->setModel(model);
        view->show();*/
           timer2->stop();
        }

        /********************************************************/

}
/*
void Dialog::on_pushButton_clicked()
{
    // Добавить
    // Если одна из ячеек для ввода данных пуста
    if (ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "")
    {
        // предупреждение
        QMessageBox::warning(this, "Ошибка", "Вы не заполнили одно из полей, перепроверьте информацию");
        // остановка дальнейшего выполнения
        return;
    }
// если значения указаны пользователем
else
{
// переменная функции записи
    QSqlRecord rec = model->record();
    // значения имени
    rec.setValue("number", ui->lineEdit->text());
    rec.setValue("name", ui->lineEdit_2->text());
    // значение возраста
    rec.setValue("url", ui->lineEdit_3->text());
    rec.setValue("operation", ui->lineEdit_4->text());

    // запись в модель (это значит что и в SQL запишется тоже самое)
    // "1" означает, что новая строка появится в самом конце списка
    model->insertRecord(-1, rec);
    // обнуляем поля ввода
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    // выравниваем высоту строк по тексту
    ui->tableView->resizeRowsToContents();
    }
}

void Dialog::on_pushButton_2_clicked()
{
    // Удалить
    // Создаем окно с выбором вариантов действий
    // создаем переменную ответа
    QMessageBox::StandardButton stButtonYes;
    // присваиваем значение, которое выберет пользователь: "Yes" или "No"
    stButtonYes = QMessageBox::question(this, "Подтверждение удаления", "Вы действительно хотите удалить строку?",
    QMessageBox::Yes | QMessageBox::No);
    // проверяем нажата ли кнопка "Yes"
    if(stButtonYes == QMessageBox::Yes)
    {
        // если нажата, то удаляем выбранную строку
        model->removeRow(ui->tableView->currentIndex().row());
        // обновляем модель
        model->select();
    }
}

void Dialog::on_pushButton_3_clicked()
{
    model->setFilter("id_technical_mean = '"+ui->idCam->text()+"'");
    model->setSort(0,Qt::DescendingOrder);
    model->select();
    QSqlRecord rec = model->record(0);
    QString strPath =  rec.value("net_address").toString();
    ui->label_7->setText(strPath);

}
*/

void DatabaseConf::on_add_clicked()
{

    // переменная функции записи
        QSqlRecord rec = model1->record();
        // значения имени
        rec.setValue("number", ui->id->text());
        rec.setValue("name",  ui->name->text());
        // значение возраста
        rec.setValue("url", ui->url->text());
        rec.setValue("operation", "NULL");

        // запись в модель (это значит что и в SQL запишется тоже самое)
        // "1" означает, что новая строка появится в самом конце списка
        model1->insertRecord(-1, rec);
        // обнуляем поля ввода
        // выравниваем высоту строк по тексту
        ui->database1->resizeRowsToContents();


}

void DatabaseConf::on_database2_clicked(const QModelIndex &index)
{
    //qDebug()<< "on_tableView_clicked";

    qDebug()<< "row";
   qDebug()<<index.row();
    qDebug()<< "column";
   qDebug()<<index.column();
    qDebug()<<  ui->database2->model()->itemData(index).values().last().toString();

    if (index.column()==2)
        ui->url->setText(ui->database2->model()->itemData(index).values().last().toString());
    if (index.column()==1)
        ui->name->setText(ui->database2->model()->itemData(index).values().last().toString());
    if (index.column()==0)
        ui->id->setText(ui->database2->model()->itemData(index).values().last().toString());

 //   QModelIndex index1 = new QModelIndex(-1,-1,0,model1);
    //qDebug()<<  ui->database2->model()->itemData(index1).values().last().toString();
    /*
    QString _number = ui->database1->model()->index(0,index.column()).data().toString();
    QString _name =  ui->database1->model()->index(1,index.column()).data().toString()  ;
    QString _url = ui->database1->model()->index(2,index.column()).data().toString();
    QString _operation = ui->database1->model()->index(4,index.column()).data().toString();

    qDebug()<<_number;
    qDebug()<<_name;
    qDebug()<<_url;
    qDebug()<<_operation;
    */
    /*
             setNumber(ui->database1->model()->index(0,index.column().data().toString()));
    setName(ui->database1->model()->index(1,index.column().data().toString()));
    setUrl(ui->database1->model()->index(2,index.column().data().toString()));
    setOperation(ui->database1->model()->index(4,0).data().toString());
    */
    /*
    if (index.column()==2)
        ui->url->setText(ui->tableView->model()->itemData(index).values().last().toString());
    */
     //qDebug()<< "***********************************";
   // qDebug()<<index();
}
/*
void  DatabaseConf::setNumber(QString param)
{
   // number = param;
}
void DatabaseConf::setName(QString param)
{
    // name = param;
}
void DatabaseConf::setUrl(QString param)
{
    // url = param;
}
void DatabaseConf::setOperation(QString param)
{
    // operation = param;
}
*/

void DatabaseConf::on_dell_clicked()
{

    // Удалить
    // Создаем окно с выбором вариантов действий
    // создаем переменную ответа
    QMessageBox::StandardButton stButtonYes;
    // присваиваем значение, которое выберет пользователь: "Yes" или "No"
    stButtonYes = QMessageBox::question(this, "Подтверждение удаления", "Вы действительно хотите удалить строку?",
    QMessageBox::Yes | QMessageBox::No);
    // проверяем нажата ли кнопка "Yes"
    if(stButtonYes == QMessageBox::Yes)
    {
        // если нажата, то удаляем выбранную строку
        model1->removeRow(ui->database1->currentIndex().row());
        // обновляем модель
        model1->select();
    }

}
/*

/ Удалить
    // Создаем окно с выбором вариантов действий
    // создаем переменную ответа
    QMessageBox::StandardButton stButtonYes;
    // присваиваем значение, которое выберет пользователь: "Yes" или "No"
    stButtonYes = QMessageBox::question(this, "Подтверждение удаления", "Вы действительно хотите удалить строку?",
    QMessageBox::Yes | QMessageBox::No);
    // проверяем нажата ли кнопка "Yes"
    if(stButtonYes == QMessageBox::Yes)
    {
        // если нажата, то удаляем выбранную строку
        model->removeRow(ui->tableView->currentIndex().row());
        // обновляем модель
        model->select();
    }*/

void DatabaseConf::on_connect_settings_db1_clicked()
{

    settingsdb1 = new ConnectSettingsDB();
    //databases->setModal(true); // говорим форме что она модальна
    settingsdb1->show();//exec(); // подтверждаем выполнение
    settingsdb1->setWindowTitle("Настройки подключения к конфигурационной базе");

}

void DatabaseConf::on_connect_settings_db2_clicked()
{

    settingsdb2 = new ConnectSettingsDB();
    //databases->setModal(true); // говорим форме что она модальна
    settingsdb2->show();//exec(); // подтверждаем выполнение
     settingsdb2->setWindowTitle("Настройки подключения к АСУПП");

}
