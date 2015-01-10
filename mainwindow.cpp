#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>

///Главный класс
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QWidget wgt;
    /*
    w = new VideoWgt("D:\\clip.avi");
    w1= new VideoWgt("D:\\clip.avi");
    w2= new VideoWgt("D:\\clip.avi");
    w3= new VideoWgt("D:\\clip.avi");
    w4= new VideoWgt("D:\\clip.avi");
    w5= new VideoWgt("D:\\clip.avi");
    */

    w = new VideoWgt("D:\\video\\Masha.i.medved_14_Lyzhnu_2011.avi");
    w1= new VideoWgt("D:\\video\\Masha.i.medved_15_Budte.zdorovj_2011.avi");
    w2= new VideoWgt("D:\\video\\Masha.i.medved_16_Masha+kasha_2011.avi");
    w3= new VideoWgt("D:\\video\\Masha.i.medved_17_Dalnij.Rodstvennik_2011.avi");
    w4= new VideoWgt("D:\\video\\Masha.i.medved_18_Bolshaya.stirka_2011.avi");
    w5= new VideoWgt("D:\\video\\Masha.i.medved_19_Repeticiya.Orkestra_2011.avi");


    /*
    _media = new VlcMedia("D:\\video\\Masha.i.medved_14_Lyzhnu_2011.avi", true, _instance);
    _media1 = new VlcMedia("D:\\video\\Masha.i.medved_15_Budte.zdorovj_2011.avi", true, _instance);
    _media2 = new VlcMedia("D:\\video\\Masha.i.medved_16_Masha+kasha_2011.avi", true, _instance);
    _media3 = new VlcMedia("D:\\video\\Masha.i.medved_17_Dalnij.Rodstvennik_2011.avi", true, _instance);
    _media4 = new VlcMedia("D:\\video\\Masha.i.medved_18_Bolshaya.stirka_2011.avi", true, _instance);
    _media5 = new VlcMedia("D:\\video\\Masha.i.medved_19_Repeticiya.Orkestra_2011.avi", true, _instance);
    */
    /*QHBoxLayout* ph = new QHBoxLayout;
    ph->setMargin(10);
    ph->setSpacing(20);
    ph->addWidget(w);
    ph->addWidget(w1);
    ph->addWidget(w3);
    wgt.setLayout(ph);
    wgt.show();*/
    QGridLayout* pgrdLayout = new QGridLayout;
/*
    pgrdLayout->setMargin(-2);
    pgrdLayout->setSpacing(-2);
    */

    pgrdLayout->setSpacing(2);


    pgrdLayout->addWidget(w,0,0);
    pgrdLayout->addWidget(w1,0,1);
    pgrdLayout->addWidget(w2,1,0);
    pgrdLayout->addWidget(w3,1,1);
    pgrdLayout->addWidget(w4,1,2);
    pgrdLayout->addWidget(w5,0,2);
    //pgrdLayout->addWidget(w3,0,0);

    //ph->addWidget(w,1,0,0);
    /*ph->addWidget(w1);
   ph->addWidget(w3);
   */
    ui->widget->setLayout(pgrdLayout);
    /*
    server = new Server(2323);
    connect(server,SIGNAL(datasent(QString)),this,SLOT(mySlot()));
    */

}


MainWindow::~MainWindow()
{
    delete ui;
    delete w;
    delete w1;
    delete w2;
    delete w3;
    delete w4;
    delete w5;
}

void MainWindow::on_showOff_clicked()
{
    w->setVisibleButtons(false);
    w1->setVisibleButtons(false);
    w2->setVisibleButtons(false);
    w3->setVisibleButtons(false);
    w4->setVisibleButtons(false);
    w5->setVisibleButtons(false);
}

void MainWindow::on_pushButton_clicked()
{
    //server->show();
}

void MainWindow::mySlot()
{
    //server->show();
}

void MainWindow::on_dbConfig_clicked()
{
    /*
     databases = new DatabaseConf();
     //databases->setModal(true); // говорим форме что она модальна
     databases->show();//exec(); // подтверждаем выполнение
     */
}
