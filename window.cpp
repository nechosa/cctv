#include "window.h"
#include "ui_window.h"

/*
Главная форма для конструкции обектов видеоизображения

*/
Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    //QRect screen = QApplication::screens().count();
    qDebug()<< QApplication::screens().count();
    worktable = 1;
    fullscr = 0;
    //setWindowTitle("Система отображения видеоинформации");

    setWindowTitle("Представление  видеоинформации");
    setWindowIcon(QIcon(":/icons/vista_189.ico"));

    /*Создаем 6 обьектов видеокамер*/
     w0 = new VideoWgt("Камера 1 ");
    // v = new Video();
     w = new VideoWgt("Камера 1 ");
     w1= new VideoWgt("Камера 2 ");
     w2= new VideoWgt("Камера 3 ");
     w3= new VideoWgt("Камера 4 ");
     w4= new VideoWgt("Камера 5 ");
     w5= new VideoWgt("Камера 6 ");

     w->setVideoWidgetTitle("Камера 1");
     w1->setVideoWidgetTitle("Камера 2");
     w2->setVideoWidgetTitle("Камера 3");
     w3->setVideoWidgetTitle("Камера 4");
     w4->setVideoWidgetTitle("Камера 5");
     w5->setVideoWidgetTitle("Камера 6");

     QGridLayout* pgrdLayout = new QGridLayout;
     pgrdLayout->setMargin(1);
     pgrdLayout->setSpacing(1);

     pgrdLayout->addWidget(w,0,0);
     pgrdLayout->addWidget(w1,0,1);
     pgrdLayout->addWidget(w2,0,2);
     pgrdLayout->addWidget(w3,1,0);
     pgrdLayout->addWidget(w4,1,1);
    // pgrdLayout->addWidget(v,1,2);
      pgrdLayout->addWidget(w5,1,2);
   //  pgrdLayout->addWidget(w6,0,3);
     ui->_wgt->setLayout(pgrdLayout);


     //server = new Server(2323);
     client = new UdpClient();
     client->setStyleSheet(this->styleSheet());
   //  v = new Video();
     //connect(server,SIGNAL(datasent(QString)),this,SLOT(mySlot(QString)));
   //  connect(w0 ,SIGNAL(close),w0,SLOT(stop()));

     //connect(client,SIGNAL(datasent(QString)),this,SLOT(play_on_UdpClient(QString)));
     connect(client,SIGNAL(datasent1(QString,unsigned int)),this,SLOT(play_in_Window(QString,unsigned int)));
     connect(ui->but,SIGNAL(clicked()),w,SLOT(setVisibleButtons()));
     connect(ui->but,SIGNAL(clicked()),w1,SLOT(setVisibleButtons()));
     connect(ui->but,SIGNAL(clicked()),w2,SLOT(setVisibleButtons()));
     connect(ui->but,SIGNAL(clicked()),w3,SLOT(setVisibleButtons()));
     connect(ui->but,SIGNAL(clicked()),w4,SLOT(setVisibleButtons()));
     connect(ui->but,SIGNAL(clicked()),w5,SLOT(setVisibleButtons()));
    //  connect(ui->but,SIGNAL(clicked()),w6,SLOT(setVisibleButtons()));
   //  server->setWindowTitle("Параметры сервера");
      QObject::connect(this,SIGNAL(destroyed()),w1,SLOT(close()));
      QObject::connect(this,SIGNAL(destroyed()),w2,SLOT(close()));
      QObject::connect(this,SIGNAL(destroyed()),w3,SLOT(close()));
      QObject::connect(this,SIGNAL(destroyed()),w4,SLOT(close()));
      QObject::connect(this,SIGNAL(destroyed()),w5,SLOT(close()));
   //   QObject::connect(this,SIGNAL(destroyed()),w,SLOT(close());

                QObject::connect(this,SIGNAL(Qt::Key_F11),this,SLOT(showOn_MaxMin()));
      /*
      QObject::connect(w,SIGNAL(doubleClick()),this,SLOT(showOn_MaxMin()));
      QObject::connect(w1,SIGNAL(doubleClick()),this,SLOT(showOn_MaxMin()));
      QObject::connect(w2,SIGNAL(doubleClick()),this,SLOT(showOn_MaxMin()));
      QObject::connect(w3,SIGNAL(doubleClick()),this,SLOT(showOn_MaxMin()));
      QObject::connect(w4,SIGNAL(doubleClick()),this,SLOT(showOn_MaxMin()));
      QObject::connect(w5,SIGNAL(doubleClick()),this,SLOT(showOn_MaxMin()));
      */
      //QObject::connect(this,SIGNAL(doubleClick()),this,SLOT(test()));
       QObject::connect(w,SIGNAL(doubleClick()),this,SLOT(test()));
       QObject::connect(w1,SIGNAL(doubleClick()),this,SLOT(showMaxCam2()));
       QObject::connect(w2,SIGNAL(doubleClick()),this,SLOT(showMaxCam3()));
       QObject::connect(w3,SIGNAL(doubleClick()),this,SLOT(showMaxCam4()));
       QObject::connect(w4,SIGNAL(doubleClick()),this,SLOT(showMaxCam5()));
       QObject::connect(w5,SIGNAL(doubleClick()),this,SLOT(showMaxCam6()));

       QObject::connect(w,SIGNAL(doubleClick()),w,SLOT(setVideoMax()));


      /*QObject::connect(ui->_wgt,SIGNAL(showOnMin()),this,SLOT(showNormal()));
      QObject::connect(ui->_wgt,SIGNAL(showOnMin()),this,SLOT(showNormal()));
      doubleClick
              */

}

Window::~Window()
{
    delete ui;
//    delete server;
    delete client;
    delete databases;
    delete w;
    delete w0;
    delete w1;
    delete w2;
    delete w3;
    delete w4;
    delete w5;
}

void Window::showMaxCam(int camera)
{
    if (this->isFullScreen())
    {

        this->showNormal();
    }
    else
        this->showFullScreen();

    ui->but->hide();
    ui->but_3->hide();
    ui->but_4->hide();
    ui->but_5->hide();

switch (camera) {
    case 1:
    {
        w1->hide();
        w2->hide();
        w3->hide();
        w4->hide();
        w5->hide();
    }
        break;
    case 2:
    {
        w->hide();
        w2->hide();
        w3->hide();
        w4->hide();
        w5->hide();
    }

        break;
    case 3:
    {
        w1->hide();
        w->hide();
        w3->hide();
        w4->hide();
        w5->hide();
    }

        break;
    case 4:
    {
        w1->hide();
        w2->hide();
        w->hide();
        w4->hide();
        w5->hide();
    }

        break;
    case 5:
    {
        w1->hide();
        w2->hide();
        w3->hide();
        w->hide();
        w5->hide();
    }

        break;
    case 6:
    {
        w1->hide();
        w2->hide();
        w3->hide();
        w4->hide();
        w->hide();
    }

        break;
    default:
        break;
}
}
void Window::test()
{
    if (this->isFullScreen())
    {
        if (!fullscr)
        this->showNormal();
    }
    else
        this->showFullScreen();
    if ((w1->isVisible())&&(w2->isVisible())&&(w3->isVisible())&&(w4->isVisible())&&(w5->isVisible()))
    {
        w1->setVisible(false);
        w2->setVisible(false);
        w3->setVisible(false);
        w4->setVisible(false);
        w5->setVisible(false);
        ui->but->hide();
        ui->but_3->hide();
        ui->but_4->hide();
        ui->but_5->hide();
    }
    else
    {
        w1->setVisible(true);
        w2->setVisible(true);
        w3->setVisible(true);
        w4->setVisible(true);
        w5->setVisible(true);
        ui->but->show();
        ui->but_3->show();
        ui->but_4->show();
        ui->but_5->show();
    }

}

void Window::showMaxCam1()
{
    if (this->isFullScreen())
    {
        if (!fullscr)
        this->showNormal();
    }
    else
        this->showFullScreen();
    if ((w1->isVisible())&&(w2->isVisible())&&(w3->isVisible())&&(w4->isVisible())&&(w5->isVisible()))
    {
        w1->setVisible(false);
        w2->setVisible(false);
        w3->setVisible(false);
        w4->setVisible(false);
        w5->setVisible(false);
        ui->but->hide();
        ui->but_3->hide();
        ui->but_4->hide();
        ui->but_5->hide();
    }
    else
    {
        w1->setVisible(true);
        w2->setVisible(true);
        w3->setVisible(true);
        w4->setVisible(true);
        w5->setVisible(true);
        ui->but->show();
        ui->but_3->show();
        ui->but_4->show();
        ui->but_5->show();
    }
}
void Window::showMaxCam2()
{
    if (this->isFullScreen())
    {
        if (!fullscr)
        this->showNormal();
    }
    else
        this->showFullScreen();
    if ((w->isVisible())&&(w2->isVisible())&&(w3->isVisible())&&(w4->isVisible())&&(w5->isVisible()))
    {
        w->setVisible(false);
        w2->setVisible(false);
        w3->setVisible(false);
        w4->setVisible(false);
        w5->setVisible(false);
        ui->but->hide();
        ui->but_3->hide();
        ui->but_4->hide();
        ui->but_5->hide();
    }
    else
    {
        w->setVisible(true);
        w2->setVisible(true);
        w3->setVisible(true);
        w4->setVisible(true);
        w5->setVisible(true);
        ui->but->show();
        ui->but_3->show();
        ui->but_4->show();
        ui->but_5->show();
    }
}
void Window::showMaxCam3()
{
    if (this->isFullScreen())
    {
        if (!fullscr)
        this->showNormal();
    }
    else
        this->showFullScreen();
    if ((w1->isVisible())&&(w->isVisible())&&(w3->isVisible())&&(w4->isVisible())&&(w5->isVisible()))
    {
        w1->setVisible(false);
        w->setVisible(false);
        w3->setVisible(false);
        w4->setVisible(false);
        w5->setVisible(false);
        ui->but->hide();
        ui->but_3->hide();
        ui->but_4->hide();
        ui->but_5->hide();
    }
    else
    {
        w1->setVisible(true);
        w->setVisible(true);
        w3->setVisible(true);
        w4->setVisible(true);
        w5->setVisible(true);
        ui->but->show();
        ui->but_3->show();
        ui->but_4->show();
        ui->but_5->show();
    }
}
void Window::showMaxCam4()
{
    if (this->isFullScreen())
    {
        if (!fullscr)
        this->showNormal();
    }
    else
        this->showFullScreen();
    if ((w1->isVisible())&&(w2->isVisible())&&(w->isVisible())&&(w4->isVisible())&&(w5->isVisible()))
    {
        w1->setVisible(false);
        w2->setVisible(false);
        w->setVisible(false);
        w4->setVisible(false);
        w5->setVisible(false);
        ui->but->hide();
        ui->but_3->hide();
        ui->but_4->hide();
        ui->but_5->hide();
    }
    else
    {
        w1->setVisible(true);
        w2->setVisible(true);
        w->setVisible(true);
        w4->setVisible(true);
        w5->setVisible(true);
        ui->but->show();
        ui->but_3->show();
        ui->but_4->show();
        ui->but_5->show();
    }
}

void Window::showMaxCam5()
{
    if (this->isFullScreen())
    {
        if (!fullscr)
        this->showNormal();
    }
    else
        this->showFullScreen();
    qDebug()<< "******************test**********************";
    if ((w1->isVisible())&&(w2->isVisible())&&(w3->isVisible())&&(w->isVisible())&&(w5->isVisible()))
    {
        w1->setVisible(false);
        w2->setVisible(false);
        w3->setVisible(false);
        w->setVisible(false);
        w5->setVisible(false);
        ui->but->hide();
        ui->but_3->hide();
        ui->but_4->hide();
        ui->but_5->hide();
    }
    else
    {
        w1->setVisible(true);
        w2->setVisible(true);
        w3->setVisible(true);
        w->setVisible(true);
        w5->setVisible(true);
        ui->but->show();
        ui->but_3->show();
        ui->but_4->show();
        ui->but_5->show();
    }
}
void Window::showMaxCam6()
{
    if (this->isFullScreen())
    {
        if (!fullscr)
        this->showNormal();
    }
    else
        this->showFullScreen();
    qDebug()<< "******************test**********************";
    if ((w1->isVisible())&&(w2->isVisible())&&(w3->isVisible())&&(w4->isVisible())&&(w->isVisible()))
    {
        w1->setVisible(false);
        w2->setVisible(false);
        w3->setVisible(false);
        w4->setVisible(false);
        w->setVisible(false);
        ui->but->hide();
        ui->but_3->hide();
        ui->but_4->hide();
        ui->but_5->hide();
    }
    else
    {
        w1->setVisible(true);
        w2->setVisible(true);
        w3->setVisible(true);
        w4->setVisible(true);
        w->setVisible(true);
        ui->but->show();
        ui->but_3->show();
        ui->but_4->show();
        ui->but_5->show();
    }
}
void Window::play_on_UdpClient(QString path)
{
    qDebug()<< "******************playOnUdpclient**********************";
    qDebug()<< path;
    w0->show();
    w0->play(path);
    //w0->play("D:\\test.mp4");
}
/*
 *void Window::play_on_UdpClient(QString path)
{
    qDebug()<< "******************playOnUdpclient**********************";
    qDebug()<< path;
    w0->show();
    w0->play(path);
    //w0->play("D:\\test.mp4");
}
char marker[5];//Заголовок пакета ASUPP
unsigned int codoper;//Код операции 2 байта
unsigned char operStatus;//Статус оперции 0-начата;1-завершена;2-вручную
unsigned char nameLenth;//Длина строки
char codeMnemo[]; //имя мнемосхемы
*/

void Window::play_in_Window(QString path,unsigned int operStatus)
{
   int minimal = 0;
   int cam = 0;
   int flag = 1;
   qDebug()<< "******************play_in_Window********************";
   qDebug()<<path;
    // path=QString("D:\\video\\Masha.i.medved_15_Budte.zdorovj_2011.avi");

   cam = map.value(path);
    /*
    qDebug()<< "******************play_in_Window****path******************";
    qDebug()<<path;
    path="D:\\test.mp4";
    qDebug()<< "******************operStatus**********************";
    qDebug()<<operStatus;
  //  operStatus=0;
    qDebug()<< "******************play_in_Window**********************";
    */
    // operStatus = 0 -
    //Статус оперции 0-начата;1-завершена;2-вручную
    if (operStatus==0)
    {
         qDebug()<< "******************status == 0**********************";

        if (minimal == w->getCount())
        {
            /*
             foreach (QString str, map.uniqueKeys()) {
                 if(path==str)
                 {
                     flag = 0;
                 }
             }
             */
             if (flag)
             {
                w->play(path);
                w->setPath(path);
                w->incCount();
                map.insert(path,1);
             }
             flag = 1;

            return;
        }
        if (minimal == w1->getCount())
        {
            /*
            foreach (QString str, map.uniqueKeys()) {
             if(path==str)
                    flag = 0;
            }
            */
            if (flag)
            {
                w1->play(path);
                w1->incCount();
                w1->setPath(path);
                map.insert(path,2);
            }
            flag = 1;
            return;
        }
        if (minimal == w2->getCount())
        {
            /*
            foreach (QString str, map.uniqueKeys()) {
             if(path==str)
                    flag = 0;
            }
            */
            if (flag)
            {
                w2->play(path);
                w2->incCount();
                w2->setPath(path);
                map.insert(path,3);
            }
             flag = 1;
            return;
        }
        if (minimal == w3->getCount())
        {
            /*
            foreach (QString str, map.uniqueKeys()) {
             if(path==str)
                    flag = 0;
            }
            */
            if (flag)
            {
                w3->play(path);
                w3->incCount();
                w3->setPath(path);
                map.insert(path,4);
            }
             flag = 1;
            return;
        }
        if (minimal == w4->getCount())
        {
            /*
            foreach (QString str, map.uniqueKeys()) {
             if(path==str)
                    flag = 0;
            }*/
            if (flag)
            {
             w4->play(path);
             w4->incCount();
             w4->setPath(path);
             map.insert(path,5);
            }
             flag = 1;
            return;
        }
        if (minimal == w5->getCount())
        {
            /*
            foreach (QString str, map.uniqueKeys()) {
             if(path==str)
                    flag = 0;
            }*/
            if (flag)
            {
             w5->play(path);
             w5->incCount();
             w5->setPath(path);
             map.insert(path,6);
            }
             flag = 1;
            return;
        }
    }
    /*****************
    if (operStatus==0)
    {
         qDebug()<< "******************status == 0**********************";

        if (minimal == w->getCount())
        {
             foreach (QString str, map.uniqueKeys()) {
                 if(path==str)
                 {
                     flag = 1;
                 }
             }
             if (flag)
             {
                w->play(path);
                w->incCount();
                map.insert(path,1);
             }
             flag = 0;

            return;
        }
        if (minimal == w1->getCount())
        {
             w1->play(path);
             w1->incCount();
             foreach (QString str, map.uniqueKeys()) {
                 if(path==str)
                 {
                     flag = 1;
                 }
             }
             map.insert(path,2);


            return;
        }
        if (minimal == w2->getCount())
        {
             w2->play(path);
             w2->incCount();
             map.insert(path,3);
            return;
        }
        if (minimal == w3->getCount())
        {
             w3->play(path);
             w3->incCount();
             map.insert(path,4);
            return;
        }
        if (minimal == w4->getCount())
        {
             w4->play(path);
             w4->incCount();
             map.insert(path,5);
            return;
        }
        if (minimal == w5->getCount())
        {
             w5->play(path);
             w5->incCount();
             map.insert(path,6);
            return;
        }
    }
     ********//////
    if (operStatus==1)//статус закрытия видео
    {
        if (cam==0)
        {
          qDebug()<< "Принятый адрес не найден в хеш таблице";
        }
        else
        {
            if (cam==1)
            {
                w->decCount();
                if (w->getCount()==0)
                {
                    map.remove(path,1);
                    /*
                    QMultiMap<QString,int>::iterator it = map.begin();
                    for (;it!=map.end();++it)
                    {
                        it.map.erase(path);
                    }
                    */
                    w->stop();
                }
            }
            if (cam==2)
            {
                w1->decCount();
                if (w1->getCount()==0)
                {
                    map.remove(path,2);
                    w1->stop();
                }
            }
            if (cam==3)
            {
                w2->decCount();
                if (w2->getCount()==0)
                {
                    map.remove(path,3);
                    w2->stop();
                }
            }
            if (cam==4)
            {
                w3->decCount();
                if (w3->getCount()==0)
                {
                    map.remove(path,4);
                    w3->stop();
                }
            }
            if (cam==5)
            {
                w4->decCount();
                if (w4->getCount()==0)
                {
                    map.remove(path,5);
                    w4->stop();
                }
            }
            if (cam==6)
            {
                w5->decCount();
                if (w5->getCount()==0)
                {
                    map.remove(path,6);
                    w5->stop();
                }
            }
        }
        qDebug()<< "******************status == 1**********************";
        /*
        int cam =0;
        cam = databases->listCam(path);
        if (cam==1)
        {
            w->decCount();
            if (w->getCount()==0)
            {
                w->stop();
            }
        }
        if (cam==2)
        {
            w1->decCount();
            if (w1->getCount()==0)
            {
                w1->stop();
            }
        }
        if (cam==3)
        {
            w2->decCount();
            if (w2->getCount()==0)
            {
                w2->stop();
            }
        }
        if (cam==4)
        {
            w3->decCount();
            if (w3->getCount()==0)
            {
                w3->stop();
            }
        }
        if (cam==5)
        {
            w4->decCount();
            if (w4->getCount()==0)
            {
                w4->stop();
            }
        }
        if (cam==6)
        {
            w5->decCount();
            if (w5->getCount()==0)
            {
                w5->stop();
            }
        }
        */
    }
    if (operStatus==2)
    {
        qDebug()<< "******************status == 2**********************";
        VideoWgt *w7 = new VideoWgt("Камера 0 ");
        w7->setVideoWidgetTitle("Камера 0");
        w7->setWindowTitle("Видеокамера");
        w7->show();
        w7->setWindowModality(Qt::WindowModal);
        QObject::connect(w7,SIGNAL(doubleClick()),w7,SLOT(showMaxCam7()));
    }


}


void Window::on_but_3_clicked()
{

    databases = new DatabaseConf();
    databases->setStyleSheet(this->styleSheet());
    databases->show();//exec(); // подтверждаем выполнение
    databases->setWindowModality(Qt::WindowModal);
    /*
    databases->setWindowFlags(Qt::WindowStaysOnTopHint);


    qDebug()<< "******************status == 2**********************";
    VideoWgt *w7 = new VideoWgt("Камера 0 ");
    w7->setVideoWidgetTitle("Камера 0");
    w7->setWindowTitle("Видеокамера");
    w7->show();
    w7->setWindowModality(Qt::WindowModal);
    w7->setWindowFlags(Qt::WindowStaysOnTopHint);
    QObject::connect(w7,SIGNAL(doubleClick()),w7,SLOT(showMaxCam7()));
    */

}

/*
void Window::on_but_2_clicked()
{
     //server->show();
}
*/

void Window::on_but_4_clicked()
{
    client->show();
    client->setWindowModality(Qt::WindowModal);
}

/*
void Window::mouseDoubleClickEvent(QMouseEvent *pe)
{
       if (this->isFullScreen())
       {
           this->showNormal();
       }
       else
           this->showFullScreen();
}
*/


void Window::showOn_MaxMin(){

     if (this->isFullScreen())
     {
         this->showNormal();
         fullscr = 0;
     }
     else
     {
         this->showFullScreen();
         fullscr = 1;
     }
}

void Window::on_but_5_clicked()
{
    if (worktable==1)
   {
        desktop =  QApplication::desktop();
    screen =  desktop->screenGeometry(1);
    this->move(QPoint(screen.x()+200,screen.y()+200));
    worktable=2;
    return;
    }
    if (worktable==2)
   {
    desktop =  QApplication::desktop();
    screen =  desktop->screenGeometry(2);
    this->move(QPoint(screen.x()+200,screen.y()+200));
      worktable=1;
      return;
    }
}
