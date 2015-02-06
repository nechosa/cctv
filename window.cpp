#include "window.h"
#include "ui_window.h"
#include <QVector>
#include <QThread>

/*
Главная форма для конструкции обектов видеоизображения
*/
Window::Window(QWidget *parent) :
    QWidget(parent),
    fullscr(0),
    worktable(QApplication::screens().count()),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    //visibleButtons = false;
    setWindowTitle(NAME_PROGRAM);
    setWindowIcon(QIcon(PATH_ICON));
    QGridLayout* pgrdLayout = new QGridLayout;
    pgrdLayout->setMargin(1);
    pgrdLayout->setSpacing(1);
    client = new UdpClient();
    databases = new DatabaseConf();
    client->setStyleSheet(this->styleSheet());
    connect(client,SIGNAL(datasent1(QString,unsigned int)),this,SLOT(play_in_Window(QString,unsigned int)));
    for(int i = 0;i<6;++i)
    {
        //thread[i] = new QThread();
        w[i] =  new VideoWgt(CAMERA+QString::number(i+1),i);
        w[i]->setVideoWidgetTitle(CAMERA+QString::number(i+1));
        if (i<3)
        {
            pgrdLayout->addWidget(w[i],0,i);
        }
        else
        {
            pgrdLayout->addWidget(w[i],1,i-3);
        }
        connect(ui->showbut,SIGNAL(clicked()),w[i],SLOT(setVisibleButtons()));
        connect(w[i],SIGNAL(doubleClick(int)),this,SLOT(showMaxCam(int)));
        /*
        connect(thread[i],SIGNAL(started(QPrivateSignal)),w[i],SLOT(play(QString)));
        connect(thread[i],SIGNAL(finished(QPrivateSignal)),w[i],SLOT(stop()));
        w[i]->moveToThread(thread[i]);
        thread[i]->start();
        */
    }



    ui->_wgt->setLayout(pgrdLayout);

    switch (worktable) {
    case 1:
        ui->but_5->setEnabled(false);
        break;
    case 2:
        screen1 =  QApplication::desktop()->screenGeometry(1);
        this->move(QPoint(screen1.x()+(screen1.width()-this->width())/4,screen1.y()+(screen1.height()-this->height())/4));
        client->move(QPoint(screen1.x()+(screen1.width()-client->width())/2,screen1.y()+(screen1.height()-client->height())/2));
        databases->move(QPoint(screen1.x()+(screen1.width()-databases->width())/2,screen1.y()+(screen1.height()-databases->height())/2));
        break;
    default:
        break;
    }
}

Window::~Window()
{
    delete ui;
    delete client;
    delete databases;
}

void Window::showMaxCam(int camera)
{
    bool visible = true;
    for(int i = 0;i<6;++i)
    {
        visible = visible&&w[i]->isVisible();
    }
    if (!fullscr)
    {
        if (this->isFullScreen())
        {
            this->showNormal();
            visible = false;
            if (worktable==2)
            {
                this->move(QPoint(screen1.x()+(screen1.width()-this->width())/4,screen1.y()+(screen1.height()-this->height())/4));
            }
        }
        else
        {
            this->showFullScreen();
            visible = true;
            if (worktable==2)
            {
                this->move(QPoint(screen1.x(),screen1.y()));
            }
        }
    }

    if (visible)
    {
        ui->showbut->hide();
        ui->but_3->hide();
        ui->param->hide();
        ui->but_5->hide();
    }
    else
    {
        ui->showbut->show();
        ui->but_3->show();
        ui->param->show();
        ui->but_5->show();
    }
    for(int i = 0;i<6;++i)
    {
        if (i!=camera)
        {
            w[i]->setVisible(!visible);
        }
    }
    return;

}

void Window::play_in_Window(QString path,unsigned int operStatus)
{
    switch (operStatus) {
    case 0:
        for(int i = 0;i<6;++i)
        {
            if (w[i]->getCount()==0)
            {
                w[i]->play(path);
                w[i]->setPath(path);
                w[i]->incCount();
            }
            else
            {
                if (path==w[i]->getPath())
                    w[i]->incCount();
                return;
            }
        }
        break;
    case 1:
        for(int i = 0;i<6;++i)
        {
            if (w[i]->getPath()==path)
                w[i]->decCount();
            if (w[i]->getCount()==0)
            {
                w[i]->stop();
            }
        }
        break;
    case 2:
        VideoWgt *w7 = new VideoWgt(CAMERA,0);
        w7->setVideoWidgetTitle(CAMERA);
        w7->show();
        w7->setWindowModality(Qt::WindowModal);
        w7->setFocus();
        w7->play(path);
        QObject::connect(w7,SIGNAL(doubleClick()),w7,SLOT(showMaxCam7()));
        if (worktable==2)
        {
            w7->move(QPoint(screen1.x()+(screen1.width()-client->width())/2,screen1.y()+(screen1.height()-client->height())/2));
        }
        break;
    }
}

void Window::on_but_3_clicked()
{
    databases->setStyleSheet(this->styleSheet());
    databases->show();//exec();
    databases->setWindowModality(Qt::WindowModal);
}

void Window::on_param_clicked()
{
    client->show();
    client->setWindowModality(Qt::WindowModal);
    client->setFocus();
}

void Window::showOn_MaxMin(){

    if (this->isFullScreen())
    {
        this->showNormal();
        fullscr = 0;
    }
    else
    {
        this->showFullScreen();
        if (worktable==2)
        {
            this->move(QPoint(screen1.x(),screen1.y()));
        }
        fullscr = 1;
    }
}

void Window::setSceen1(QDesktopWidget *desktop){
    if (fullscr)
    {
        screen =  desktop->screenGeometry(1);
        this->move(QPoint(screen.x(),screen.y()));
        client->move(QPoint(screen.x()+(screen.width()-client->width())/2,screen.y()+(screen.height()-client->height())/2));
        databases->move(QPoint(screen.x()+(screen.width()-databases->width())/2,screen.y()+(screen.height()-databases->height())/2));


    }
    else
    {
        screen1 =  desktop->screenGeometry(1);
        this->move(QPoint(screen1.x()+(screen1.width()-this->width())/2,screen1.y()+(screen1.height()-this->height())/2));
        client->move(QPoint(screen1.x()+(screen1.width()-client->width())/2,screen1.y()+10+(screen1.height()-client->height())/2));
        databases->move(QPoint(screen1.x()+(screen1.width()-databases->width())/2,screen1.y()+(screen1.height()-databases->height())/2));
    }
}

void Window::setSceen2(QDesktopWidget *desktop){
    if (fullscr)
    {
        screen =  desktop->screenGeometry(2);
        this->move(QPoint(screen.x()/*+(screen.width()-this->width())/2*/,screen.y()/*+(screen.height()-this->height())/2)*/));
        client->move(QPoint(screen.x()+(screen.width()-client->width())/2+screen1.width()/2-100,screen.y()-100+(screen.height()-client->height())/2+screen1.height()/2-100));
        databases->move(QPoint(screen.x()+(screen.width()-databases->width()+screen1.width())/2,screen.y()+(screen2.height()-databases->height())/2+screen1.height()/2-100));
    }
    else
    {
        screen2 =  desktop->screenGeometry(2);
        this->move(QPoint(screen2.x()+(screen2.width()-this->width())/2+screen1.width()/2-100,screen2.y()+(2*screen2.height()-this->height())/2+screen1.height()/2-100));
        client->move(QPoint(screen2.x()+(screen2.width()-client->width())/2+screen1.width()/2-100,screen2.y()-100+(screen2.height()-client->height())/2+screen1.height()/2-100));
        databases->move(QPoint(screen2.x()+(screen2.width()-databases->width()+screen1.width())/2,screen2.y()+(screen2.height()-databases->height())/2+screen1.height()/2-100));
    }
}

void Window::setSceens()
{
    if (worktable==1)
    {
        setSceen1(QApplication::desktop());
        worktable=2;
        return;
    }

    if (worktable==2)
    {
        setSceen2(QApplication::desktop());
        worktable=1;
        return;
    }
}

void Window::on_but_5_clicked()
{
    setSceens();
}

void  Window::keyPressEvent(QKeyEvent *event)
{
    key1 = event->key();
}

void Window::help()
{
    //QString strCommand="cmd.exe"; QString strCommand="help_sys.exe --number";
    v_process = new QProcess();
    QString strCommand="help_sys";
    QStringList arguments;
    arguments << "--number" <<"1";

    qDebug()<<"Try start "<<strCommand;
    v_process->start(strCommand,arguments);
    if (v_process->waitForStarted())
    {
        qDebug()<<"start process "<<strCommand;
    }
    else
    {
        qDebug()<<"Cannot start process "<<strCommand;
        v_process->execute(strCommand,arguments);
    }


}

void Window::keyReleaseEvent(QKeyEvent *event){
    if(event->key()!=key1)
    {
        return;
    }
    key1 = 0;
    switch (event->key()) {
    case Qt::Key_F5:
        showOn_MaxMin();
        break;
    case Qt::Key_X:
        qDebug()<<"x"<<this->x();
        break;
    case Qt::Key_Y:
        qDebug()<<"y"<< this->y();
        break;
    case Qt::Key_F1:
        qDebug()<<"F1";
        this->help();
        break;

    case Qt::Key_S:
        w[0]->setVisibleButtons();
        w[1]->setVisibleButtons();
        w[2]->setVisibleButtons();
        w[3]->setVisibleButtons();
        w[4]->setVisibleButtons();
        w[5]->setVisibleButtons();
        break;
    default:
        break;
    }
}
