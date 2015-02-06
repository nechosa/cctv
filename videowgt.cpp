#include "videowgt.h"
//#include "param.h"
#include "ui_videowgt.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QDebug>




VideoWgt::VideoWgt(QString Title,int camera,QWidget *parent) :
  QWidget(parent),
  ui(new Ui::VideoWgt),
  count(0),
  visibleControlButtons(false),
  visibleButtons(false)
{
    //setVisibleButtons(false);
  ui->setupUi(this);
  ui->play->hide();
  ui->param->hide();
  ui->record->hide();
  ui->onMaxWindow->hide();
  ui->stop->hide();
  setCamera(camera);
  ui->groupBox->setWindowTitle(Title);
  ui->groupBox->installEventFilter(this);
  ui->video->installEventFilter(this);

  _instance = new VlcInstance(VlcCommon::args(), this);
  _player = new VlcMediaPlayer(_instance);
  _player->setVideoWidget(ui->video);


  ui->volume->setMediaPlayer(_player);
  ui->volume->setVolume(0);
  ui->volume->setVisible(false);
    _error->errmsg();

  connect(ui->stop, SIGNAL(clicked()), _player, SLOT(stop()));
  connect(ui->play, SIGNAL(clicked()), _player, SLOT(play()));
 // connect(_player, SIGNAL()), this, SLOT(error(bool)));

  QObject::connect(this,SIGNAL(sigClose()),_player,SLOT(stop()));
  QObject::connect(this,SIGNAL(clicked()),SLOT(mySlot()));
  QObject::connect(ui->groupBox,SIGNAL(clicked()),SLOT(mySlot()));
  // QObject::connect( _player,SIGNAL(),this,SLOT(test()));
  /*************************************************
     * Заглушка для воспоизведения видео
     * так как библиотека выдает ошибку, если не воспроизводится ни одного файла или потока
     */

  _media = new VlcMedia("test.mp4", true, _instance);
  _player->open(_media);
  _player->stop();

  /*************************************************/
  par = new Param(path);
  par->setStyleSheet(this->styleSheet());

  // this->setStyleSheet(styleSheet()+"\n image: url(:/icons/logo.png);\n");

  //  connect(par,SIGNAL(datasent(QString)),this,SLOT(mySlot(QString)));
  connect(par,SIGNAL(datasent(QString)),this,SLOT(play(QString)));
  //  QObject::connect(this,SIGNAL(doubleClick()),SLOT(showFullScreen()));


}

void VideoWgt::error(bool swith)
{
    qDebug()<<"error";

}
void VideoWgt::setCamera(int cam)
{
  this->camera = cam;
}
int VideoWgt::getCamera()
{
  return camera;

}
void VideoWgt::incCount()
{
  count++;
}
void VideoWgt::decCount()
{
  count--;
}
int VideoWgt::getCount() const
{
  return count;
}

/*
 void VideoWgt::setCount(int n)
 {
     count = n;
 }
 */

void VideoWgt::setVideoMax()
{
  ui->video->setMaximumWidth(ui->groupBox->maximumHeight()-100);
}
void VideoWgt::closeEvent(QCloseEvent *event)
{
  this->~VideoWgt();
  /*
    emit sigClose();
    event->accept();
    */
}

void VideoWgt::setvisibleControlButtons()
{
  /*
    ui->play->show();
    ui->param->show();
    ui->onMaxWindow->show();
    ui->record->show();
      ui->stop->show();
      */


  /*
    if (!visibleControlButtons)
    {
    ui->play->hide();
    ui->param->hide();
     ui->record->hide();
       ui->onMaxWindow->hide();
       ui->stop->hide();
    }
    */
  if (!visibleControlButtons)
    {
      visibleControlButtons = true;
      ui->play->show();
      ui->param->show();
      ui->onMaxWindow->show();
      ui->record->show();
      ui->stop->show();
    }
  else
    {
      visibleControlButtons = false;
      ui->play->hide();
      ui->param->hide();
      ui->record->hide();
      ui->onMaxWindow->hide();
      ui->stop->hide();
    }
}
bool VideoWgt::getvisibleControlButtons() const
{
  return visibleControlButtons;
}
bool VideoWgt::eventFilter(QObject *obj, QEvent *event)
{
  if ((obj== ui->groupBox))
    {
      if (event->type()==QEvent::MouseButtonDblClick)
        {
          qDebug()<<"MouseMove";
          // QMouseEvent *mouseEvent = static_cast<QMouseEvent>(event)
          return true;
        }
      else
        return QObject::eventFilter(obj,event);
    }
  if ((obj== ui->video))
    {
      if (event->type()==QEvent::MouseButtonDblClick)
        {
          qDebug()<<"  emit doubleClick();";
          //setvisibleControlButtons();
          // emit doubleClick();

          // QMouseEvent *mouseEvent = static_cast<QMouseEvent>(event)
          return true;
        }
      else
        if (event->type()==QEvent::MouseButtonPress)
          {
            qDebug()<<"  emit MouseButtonPress();";
            emit doubleClick(getCamera());
            //setvisibleControlButtons();
            return true;
          }
        else
          return QObject::eventFilter(obj,event);
    }
  if ((obj== ui->video->window()))
    {
      if (event->type()==QEvent::MouseButtonDblClick)
        {
          qDebug()<<"  emit doubleClick();";
          emit doubleClick(getCamera());
          // QMouseEvent *mouseEvent = static_cast<QMouseEvent>(event)
          return true;
        }
      else
        return QObject::eventFilter(obj,event);
    }
  return false;

}

void VideoWgt::mySlot()
{
  qDebug()<<"mySlot";
}

void VideoWgt::setPath(QString newpath)
{
  path = newpath;
  par->setUrl(path);
}
QString VideoWgt::getPath()
{
    return path;
}

void VideoWgt::play(QString path)
{
  if (path.isEmpty())
    return;
  qDebug()<<"play";
  qDebug()<<path.contains("rtsp:");
 if (path.contains("rtsp")||path.contains("udp"))
 // if ((path.mid(0,3)=="udp")||(path.mid(0,5)=="rtsp:"))
    //if ((path.compare(path,"rtsp://",Qt::CaseInsensitive)==1)&&(path.compare(path.mid(0,5),"udp://",Qt::CaseInsensitive)==1))
    /*&&(path.compare(path,"udp://",Qt::CaseInsensitive)==1)&&(path.compare(path,"http://",Qt::CaseInsensitive)==1)&&
        (path.compare(path,"rtp://",Qt::CaseInsensitive)==1)&&
        (path.compare(path,"mms://",Qt::CaseInsensitive)==1))*/
    {
      qDebug()<<"stream";
      _media = new VlcMedia(path, false, _instance);

      _media->setOption(" :network-caching=1000");
      _player->open(_media);
    }
  else
    {
      //qDebug()<<"file";
      _media = new VlcMedia(path, true, _instance);
      _player->open(_media);
    }
  setPath(path);

}
void VideoWgt::stop()
{
  _player->stop();
}



void VideoWgt::openUrl()
{

}

VideoWgt::~VideoWgt()
{    
  qDebug()<<"Free VideoWgt";
  delete ui;
  delete _player;
  delete _media;
  delete _instance;
  qDebug()<<"Delete All";
}

void VideoWgt::setNumber(int n)
{
  number = n;
}
void VideoWgt::on_onMaxWindow_clicked()
{
  emit maxWindow();
  /*
    VlcWidgetVideo *videoWgt1 = new VlcWidgetVideo;
    qDebug() << "showFullScreen();";
    VlcMedia *media6 = new VlcMedia(path, true, _instance);
    VlcMediaPlayer *player = new VlcMediaPlayer(_instance);

    player->setVideoWidget(videoWgt1);
    videoWgt1->showFullScreen();
   // videoWgt1->showNormal();
    player->open(media6);
    */

}

void VideoWgt::on_param_clicked()
{

  par->show();//exec(); // подтверждаем выполнение

}
/*
void  VideoWgt::setVisibleButtons(bool visible)
{
    visibleButtons = visible;
}
*/
void VideoWgt::setVisibleButtons()
{

  if (visibleButtons)
    {
      ui->play->setVisible(false);
      ui->stop->setVisible(false);
      ui->record->setVisible(false);
      ui->onMaxWindow->setVisible(false);
      ui->param->setVisible(false);
      visibleButtons = false;
    }
  else
    {
      ui->play->setVisible(true);
      ui->stop->setVisible(true);
      ui->record->setVisible(true);
      //  ui->onMaxWindow->setVisible(true);
      ui->param->setVisible(true);
      visibleButtons = true;
    }
  qDebug()<< "TRY SET";

}

bool VideoWgt::isVisibleButtons()
{
  // if  (ui->play->isVisible()&&ui->stop->)
  return false;
}

void VideoWgt::on_record_clicked()
{
       qDebug()<<"***********************************************time***********************************************";
       qDebug()<<_player->time();
       qDebug()<<_player->registerUserData();
       qDebug()<<_player->dynamicPropertyNames();
       qDebug()<<_player->length();
       qDebug()<<_player->position();
  /*
    capture.release();
    if (!capture.open(0)) {
        qWarning() << tr("error: capWebCam not accessed successfully");
        return;
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGui()));
    timer->start(20);
    if (ui->video->isVisible())
    {
     ui->video->setVisible(false);
     ui->label->setVisible(true);
    }
    else
    {
     ui->video->setVisible(true);
     ui->label->setVisible(false);
    }
    */
  /*
    _media = new VlcMedia("ui->editUrl->text()", _instance);
    _media->record("ui->editName->text()","ui->editPath->text()",
                   Vlc::Mux(par->intmux()),
                   Vlc::AudioCodec(par->intaudio()),
                   Vlc::VideoCodec(par->intvideo())
                   );
    _player->open(_media);
    _timer->start(20000);
    */

}

void VideoWgt::processFrameAndUpdateGui()
{
  /*
    if (capture.read(mat)) {
        QImage image((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
    */
}
void VideoWgt::on_play_clicked()
{

}

void VideoWgt::on_stop_clicked()
{

}

void VideoWgt::setVideoWidgetTitle(QString title)
{
  ui->groupBox->setTitle(title);
}

void VideoWgt::on_volume_clicked()
{

}

void VideoWgt::on_but_volume_clicked()
{

}

void VideoWgt::on_video_fullscreen()
{

}
void VideoWgt::enterEvent(QEvent *)
{
  /*
    ui->play->show();
    ui->param->show();
    ui->onMaxWindow->show();
    ui->record->show();
      ui->stop->show();
      */
}
void VideoWgt::setWindowScreen(int screen,QDesktopWidget * desktopWindow){
  worktable = screen;
}
void VideoWgt::leaveEvent(QEvent *)
{
  /*
    if (!visibleControlButtons)
    {
    ui->play->hide();
    ui->param->hide();
     ui->record->hide();
       ui->onMaxWindow->hide();
       ui->stop->hide();
    }
    */
}
/*
void VideoWgt::on_horizontalSlider_actionTriggered(int action)
{

}

void VideoWgt::on_verticalSlider_actionTriggered(int action)
{
}
*/
/*
void VideoWgt::on_horizontalSlider_sliderMoved(int position)
{
    ui->volume->setVolume(position);
     qDebug()<< position;
}
*/

void VideoWgt::on_groupBox_clicked()
{
  this->setVisibleButtons();
}

void VideoWgt::on_groupBox_clicked(bool checked)
{
  this->setVisibleButtons();
}

void VideoWgt::on_video_clicked()
{
  this->setVisibleButtons();
}

void VideoWgt::showMaxCam7()
{



  if (this->isFullScreen())
    {
      screen =  QApplication::desktop()->screenGeometry(1);
      this->move(QPoint(screen.x()+(screen.width()-this->width())/4,screen.y()+(screen.height()-this->height())/4));
      this->showNormal();
    }
  else
    {
      this->showFullScreen();
      screen =  QApplication::desktop()->screenGeometry(1);
      this->move(QPoint(screen.x()+(screen.width()-this->width())/4,screen.y()+(screen.height()-this->height())/4));
    }
}
