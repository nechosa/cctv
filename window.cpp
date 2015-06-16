#include "window.h"
#include "ui_window.h"
#include <QVector>
#include <QDebug>
#define SETXY(x0,x1,w) x0+(int)(x1-w)/2
//screen.x()+(int)(screen.width()-this->width())/2;
/*
Главная форма для конструкции обектов видеоизображения
*/
Window::Window(QWidget *parent) :
    QWidget(parent),
    fullscr(0),
    lay(false),
    worktable(QApplication::screens().count()),
    panel(false),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    setWindowTitle(NAME_PROGRAM);
    setWindowIcon(QIcon(PATH_ICON));

    client = new UdpClient();
    databases = new DatabaseConf();
    client->setStyleSheet(this->styleSheet());
    connect(client,SIGNAL(datasent1(QString,unsigned int)),this,SLOT(play_in_Window(QString,unsigned int)));
    connect(ui->move,SIGNAL(clicked()),this,SLOT(moveScreen()));
    connect(ui->but_3,SIGNAL(clicked()),this,SLOT(showBase()));
    connect(ui->param,SIGNAL(clicked()),this,SLOT(showClient()));
    connect(ui->bt_layout6,SIGNAL(clicked()),this,SLOT(layout6()));
    connect(ui->bt_layout4,SIGNAL(clicked()),this,SLOT(layout4()));
    connect(ui->bt_layout2_h,SIGNAL(clicked()),this,SLOT(layout2_h()));
    connect(ui->bt_layout2_v,SIGNAL(clicked()),this,SLOT(layout2_v()));
    connect(ui->bt_layout3_h,SIGNAL(clicked()),this,SLOT(layout3_h()));
    connect(ui->bt_layout3_v,SIGNAL(clicked()),this,SLOT(layout3_v()));
    connect(ui->bt_layout4_h,SIGNAL(clicked()),this,SLOT(layout4_h()));
    connect(ui->bt_layout4_v,SIGNAL(clicked()),this,SLOT(layout4_v()));
    connect(ui->layout,SIGNAL(clicked()),this,SLOT(showLayout()));

    showLayout();
    showPanel();



    initScreen();

    //initSettings();

    QFile file(PATH_SETTINGS);
    if (!file.exists())
    {
        initSettings();
        setLayoutType(6);
    }
    else
    {

        settings = new QSettings(PATH_SETTINGS, QSettings::IniFormat,this);
        loadSettings();
    }
}

void Window::initScreen()
{
    int scr = QApplication::screens().count();
#ifdef DEFAULT_SCREEN
    scr = 0;
#endif

    switch (scr) {
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
}

void Window::showPanel()
{
    if (panel)
    {
        ui->param->setVisible(true);
        ui->but_3->setVisible(true);
        ui->showbut->setVisible(true);
        ui->layout->setVisible(true);
        ui->move->setVisible(true);
        panel = false;
    }
    else
    {
        ui->param->setVisible(false);
        ui->but_3->setVisible(false);
        ui->showbut->setVisible(false);
        ui->layout->setVisible(false);
        ui->move->setVisible(false);
        panel = true;
    }
}
void Window::showLayout()
{
    if (lay)
    {
        ui->bt_layout2_h->setVisible(true);
        ui->bt_layout2_v->setVisible(true);
        ui->bt_layout3_h->setVisible(true);
        ui->bt_layout3_v->setVisible(true);
        ui->bt_layout4_h->setVisible(true);
        ui->bt_layout4_v->setVisible(true);
        ui->bt_layout4->setVisible(true);
        ui->bt_layout6->setVisible(true);
        lay = false;
    }
    else
    {
        ui->bt_layout2_h->setVisible(false);
        ui->bt_layout2_v->setVisible(false);
        ui->bt_layout3_h->setVisible(false);
        ui->bt_layout3_v->setVisible(false);
        ui->bt_layout4_h->setVisible(false);
        ui->bt_layout4_v->setVisible(false);
        ui->bt_layout4->setVisible(false);
        ui->bt_layout6->setVisible(false);
        lay = true;
    }
}
void Window::layoutx(int num)
{
    while (w.size()>num) {
        QObject::disconnect(ui->showbut,SIGNAL(clicked()),w[w.size()-1],SLOT(setVisibleButtons()));
        QObject::disconnect(w[w.size()-1],SIGNAL(doubleClick(int)),this,SLOT(showMaxCam(int)));
        delete w[w.size()-1];
        w.pop_back();
    }
    while (w.size()<num) {
        w.push_back(new VideoWgt(CAMERA+QString::number(w.size()+1),w.size()));
        w[w.size()-1]->setVideoWidgetTitle(CAMERA+QString::number(w.size()));
        QObject::connect(ui->showbut,SIGNAL(clicked()),w[w.size()-1],SLOT(setVisibleButtons()));
        QObject::connect(w[w.size()-1],SIGNAL(doubleClick(int)),this,SLOT(showMaxCam(int)));
    }

    QGridLayout *layx = new QGridLayout();
    for(int i = 0;i<num;++i)
    {
        if (i<((num/2)))
        {
            layx->addWidget(w[i],0,i);
        }
        else
        {
            layx->addWidget(w[i],1,i-(num/2));
        }
    }

    delete ui->_wgt->layout();
    ui->_wgt->setLayout(layx);
}


void Window::layoutx_h(int num)
{
    while (w.size()<num) {
        w.push_back(new VideoWgt(CAMERA+QString::number(w.size()+1),w.size()));
        w[w.size()-1]->setVideoWidgetTitle(CAMERA+QString::number(w.size()));
        QObject::connect(ui->showbut,SIGNAL(clicked()),w[w.size()-1],SLOT(setVisibleButtons()));
        QObject::connect(w[w.size()-1],SIGNAL(doubleClick(int)),this,SLOT(showMaxCam(int)));
    }
    while (w.size()>num) {
        QObject::disconnect(ui->showbut,SIGNAL(clicked()),w[w.size()-1],SLOT(setVisibleButtons()));
        QObject::disconnect(w[w.size()-1],SIGNAL(doubleClick(int)),this,SLOT(showMaxCam(int)));
        delete w[w.size()-1];
        w.pop_back();
    }
    QGridLayout *layx_h = new QGridLayout();
    for (int i=0;i<num;++i)
    {
        layx_h->addWidget(w[i],0,i);
    }
    delete ui->_wgt->layout();
    ui->_wgt->setLayout(layx_h);
}

void Window::layoutx_v(int num)
{
    while (w.size()>num) {
        QObject::disconnect(ui->showbut,SIGNAL(clicked()),w[w.size()-1],SLOT(setVisibleButtons()));
        QObject::disconnect(w[w.size()-1],SIGNAL(doubleClick(int)),this,SLOT(showMaxCam(int)));
        delete w[w.size()-1];
        w.pop_back();
    }
    QGridLayout *layx_v = new QGridLayout();
    for (int i=0;i<num;++i)
    {
        layx_v->addWidget(w[i],i,0);
    }
    delete ui->_wgt->layout();
    ui->_wgt->setLayout(layx_v);
}

void Window::layout2_h()
{
    layoutx_h(2);
    layout_type = 1;
}

void Window::layout2_v()
{
    layoutx_v(2);
    layout_type = 2;
}

void Window::layout4()
{
    layoutx(4);
    layout_type = 3;
}
void Window::layout3_h()
{
    layoutx_h(3);
    layout_type = 4;
}
void Window::layout3_v()
{
    layoutx_v(3);
    layout_type = 5;
}

void Window::layout6()
{
    layoutx(6);
    layout_type = 6;
}

void Window::layout4_h()
{
    layoutx_h(4);
    layout_type = 7;
}

void Window::layout4_v()
{
    layoutx_v(4);
    layout_type = 8;
}

void Window::setLayoutType(int layout)
{
    switch (layout) {
    case 1:
        layout2_h();
        break;
    case 2:
        layout2_v();
        break;
    case 3:
        layout4();
        break;
    case 4:
        layout3_h();
        break;
    case 5:
        layout3_v();
        break;
    case 6:
        layoutx(6);
        break;
    case 7:
        layout4_h();
        break;
    case 8:
        layout4_v();
        break;
    default:
        layout6();
        break;

    }

}
int Window::getLayoutType()
{
    return layout_type;
}
void Window::initSettings()
{
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

}
Window::~Window()
{
    saveSettings();
    w.clear();
    delete ui;
    delete client;
    delete databases;

}

void Window::showMaxCam(int camera)
{
    bool visible = true;
    for(int i = 0;i<w.size();++i)
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
    for(int i = 0;i<w.size();++i)
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
    //добавить итератор
    switch (operStatus) {
    case 0:
        for(int i = 0;i<w.size();++i)
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
        for(int i = 0;i<w.size();++i)
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

void Window::showBase()
{
    databases->setStyleSheet(this->styleSheet());
    databases->show();//exec();
    databases->setWindowModality(Qt::WindowModal);
}

void Window::showClient()
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
    QStringList arguments;
    arguments << HELP_ARG1 <<HELP_ARG2;
    v_process->start(HELP,arguments);
    if (v_process->waitForStarted())
    {
        qDebug()<<"start process "<<HELP;
    }
    else
    {
        qDebug()<<"Cannot start process "<<HELP;
        v_process->execute(HELP,arguments);
    }
}

void Window::saveSettings()
{
    settings->beginGroup(SET_BEGIN_GRP);
    settings->setValue(SET_GEOMETRY,geometry());
    settings->setValue(SCREEN,worktable);
    settings->beginGroup(SET_CLIENT);
    settings->setValue(SET_GEOMETRY,geometry());
    settings->beginGroup(SET_DB);
    settings->setValue(SET_GEOMETRY,geometry());
    settings->beginGroup(SET_LAYOUT);
    settings->setValue(SET_LAYOUT,getLayoutType());
    settings->endGroup();
    settings->endGroup();
    settings->endGroup();
    settings->endGroup();

}

void Window::loadSettings()
{
    settings->beginGroup(SET_BEGIN_GRP);
    this->setGeometry(settings->value(SET_GEOMETRY,QRect(this->x(),this->y(),this->width(),this->height())).toRect());
    worktable = settings->value(SCREEN,0).toInt();
    settings->beginGroup(SET_CLIENT);
    client->setGeometry(settings->value(SET_GEOMETRY,QRect(client->x(),client->y(),client->width(),client->height())).toRect());
    settings->beginGroup(SET_DB);
    databases->setGeometry(settings->value(SET_GEOMETRY,QRect(databases->x(),databases->y(),databases->width(),databases->height())).toRect());
    settings->beginGroup(SET_LAYOUT);
    setLayoutType(settings->value(SET_LAYOUT,0).toInt());

    settings->endGroup();
    settings->endGroup();
    settings->endGroup();
    settings->endGroup();
}

void Window::keyReleaseEvent(QKeyEvent *event){
    if(event->key()!=key1)
    {
        return;
    }
    key1 = 0;
    switch (event->key()) {
    case Qt::Key_K:
        qDebug()<<"K";
        showLayout();
        break;
    case Qt::Key_B:
        qDebug()<<"Base";
        showBase();
        break;
    case Qt::Key_C:
        qDebug()<<"Client";
        showClient();
        break;
    case Qt::Key_P:
        qDebug()<<"Panel";
        showPanel();
        break;
    case Qt::Key_M:
        qDebug()<<"Move";
        moveScreen();
        break;

    case Qt::Key_F5:
        showOn_MaxMin();
        break;
    case Qt::Key_F1:
        qDebug()<<"F1";
        this->help();
        break;

    case Qt::Key_S:
        for(int i = 0;i<w.size();++i)
        {
            w[i]->setVisibleButtons();
        }
        break;
    default:
        break;
    }
}
