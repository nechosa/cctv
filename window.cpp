#include "window.h"
#include "ui_window.h"
#include <QVector>
#define SETXY(x0,x1,w) x0+(int)(x1-w)/2
//screen.x()+(int)(screen.width()-this->width())/2;
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


    setWindowTitle(NAME_PROGRAM);
    setWindowIcon(QIcon(PATH_ICON));
    QGridLayout* pgrdLayout = new QGridLayout;
    pgrdLayout->setMargin(1);
    pgrdLayout->setSpacing(1);
    client = new UdpClient();
    databases = new DatabaseConf();
    client->setStyleSheet(this->styleSheet());
    connect(client,SIGNAL(datasent1(QString,unsigned int)),this,SLOT(play_in_Window(QString,unsigned int)));
    connect(ui->move,SIGNAL(clicked()),this,SLOT(moveScreen()));
    for(int i = 0;i<6;++i)
    {
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
    }
    ui->_wgt->setLayout(pgrdLayout);




    switch (QApplication::screens().count()) {
    case 2:
        worktable = 1;
       // worktable = 0;
        break;
    case 1:
    default:
        ui->move->setEnabled(false);
        worktable = 0;
        //worktable = 1;
        break;

    }
   // screen = QApplication::desktop()->screenGeometry(worktable);
   // worktable = !worktable;
    screen = QApplication::desktop()->screenGeometry(worktable);

    int this_x1 = SETXY(screen.x()-200,screen.width(),this->width());
    int this_y1 = SETXY(screen.y()-150,screen.height(),this->height());
    int cli_x1 = SETXY(screen.x(),screen.width(),client->width());
    int cli_y1 = SETXY(screen.y(),screen.height(),client->height());
    int db_x1 = SETXY(screen.x(),screen.width(),databases->width());
    int db_y1 = SETXY(screen.y(),screen.height(),databases->height());
    this->setGeometry(this_x1,this_y1,this->width(),this->height());
    client->setGeometry(cli_x1,cli_y1,client->width(),client->height());
    databases->setGeometry(db_x1,db_y1,databases->width(),databases->height());

    //screen = QApplication::desktop()->screenGeometry(worktable);
    //Add Settings
    //this->setGeometry();
    //client->setGeometry();
    //databases->setGeometry();

    //No Settings
    /*
    worktable = !worktable;
    moveScreen();
    */


 //worktable = 1;
    //settings = new QSettings("D:\\wsettings.ini", QSettings::IniFormat,this);
   // loadSettings();
}

Window::~Window()
{
    saveSettings();
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
            moveScreen(false);
        }
        else
        {
            this->showFullScreen();
            visible = true;
            moveScreen(false);
        }
    }

    if (visible)
    {
        ui->showbut->hide();
        ui->but_3->hide();
        ui->param->hide();
        ui->move->hide();
    }
    else
    {
        ui->showbut->show();
        ui->but_3->show();
        ui->param->show();
        ui->move->show();
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
        if (worktable)
        {
            int w7_x1 = SETXY(screen.x(),screen.width(),w7->width());
            int w7_y1 = SETXY(screen.y(),screen.height(),w7->height());
            w7->setGeometry(w7_x1,w7_y1,w7->width(),w7->height());

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
        fullscr = 0;
        moveScreen(false);//при перемещении формы сбрасывается флаг установки полного экрана
        this->showNormal();
    }
    else
    {
        this->showFullScreen();//для сохранения расширения первого экрана
        fullscr = 1;
        moveScreen(false);//при перемещении формы сбрасывается флаг установки полного экрана
        this->showFullScreen();//установка флага полного экрана
    }
}

void Window::moveScreen(bool change ){
    if (fullscr)
    {
        if (change)
        {
            worktable = !worktable;
        }
         screen = QApplication::desktop()->screenGeometry(worktable);
         this->setGeometry(screen.x(),screen.y(),this->width(),this->height());
         int cli_x1 = SETXY(screen.x(),screen.width(),client->width());
         int cli_y1 = SETXY(screen.y(),screen.height(),client->height());
         int db_x1 = SETXY(screen.x(),screen.width(),databases->width());
         int db_y1 = SETXY(screen.y(),screen.height(),databases->height());
         client->setGeometry(cli_x1,cli_y1,client->width(),client->height());
         databases->setGeometry(db_x1,db_y1,databases->width(),databases->height());
    }
    else
    {
        if (change)
        {
            worktable = !worktable;
        }
        screen = QApplication::desktop()->screenGeometry(worktable);
        int this_x1 = SETXY(screen.x(),screen.width(),this->width());
        int this_y1 = SETXY(screen.y(),screen.height(),this->height());
        int cli_x1 = SETXY(screen.x(),screen.width(),client->width());
        int cli_y1 = SETXY(screen.y(),screen.height(),client->height());
        int db_x1 = SETXY(screen.x(),screen.width(),databases->width());
        int db_y1 = SETXY(screen.y(),screen.height(),databases->height());
        this->setGeometry(this_x1,this_y1,this->width(),this->height());
        client->setGeometry(cli_x1,cli_y1,client->width(),client->height());
        databases->setGeometry(db_x1,db_y1,databases->width(),databases->height());
    }

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

void Window::saveSettings()
{

}

void Window::loadSettings()
{
    //setWindowsTitle(settings->value("title","MainForm").toString());
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
