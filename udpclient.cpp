#include "udpclient.h"
#include "ui_udpclient.h"

UdpClient::UdpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UdpClient)
{
    ui->setupUi(this);
    //setWindowTitle("UdpClient");
    m_pudp = new QUdpSocket;
    bool rez =m_pudp->bind(8554);
    qDebug()<<m_pudp->errorString();
    //append("Received:"+dateTime.toString());
    if (!rez)
    {
        qWarning("Port  %i can't be open", 8554);
        ui->log->append("Port "+ui->lineEdit->text()+ " can't be open");
    }
    else
        qWarning("Port %i is open!", 8554);
    ui->log->append("Port  "+ui->lineEdit->text()+"  is open");
    connect(m_pudp,SIGNAL(readyRead()),SLOT(slotProcessDatagrams()));
}
void UdpClient::slotProcessDatagrams()
{
    QByteArray baDatagram;
    do
    {
        baDatagram.resize(m_pudp->pendingDatagramSize());
        m_pudp->readDatagram(baDatagram.data(),baDatagram.size());

    }while(m_pudp->hasPendingDatagrams());

    asupMnenoTest * sendMnemoTest = (asupMnenoTest*)baDatagram.data();
    sendMnemoTest->marker[5]='\0';
    int ret;
    ret = qstrcmp(sendMnemoTest->marker,"ASVID");
    ui->log->append("---------Принят пакет ---------");
    ui->log->append(sendMnemoTest->marker);

    if (!ret)
    {
        qDebug()<<"*************Packet*******************";
        qDebug()<<sendMnemoTest->codeMnemo;
        qDebug()<<sendMnemoTest->marker;
        qDebug()<<sendMnemoTest->operStatus;
        qDebug()<<sendMnemoTest->codoper;
        qDebug()<<sendMnemoTest->nameLenth;

        ui->log->append("---------Принят пакет ---------");
        ui->log->append("marker = "+  QString(sendMnemoTest->marker));
        ui->log->append("operStatus = "+ QString::number(sendMnemoTest->operStatus));
        ui->log->append("codoper = "+ QString::number(sendMnemoTest->codoper));
        ui->log->append("codeMnemo = "+ QString(sendMnemoTest->codeMnemo));
        ui->log->append("nameLenth = "+ QString::number(sendMnemoTest->nameLenth));


        int cod = (int) sendMnemoTest->codoper; //unsigned int cod = -256;
        ui->log->append("cod = "+ QString::number(cod));
        ui->log->append("--------------------------------------------------------");
        if (cod>=0)
        {
              emit datasent1(QString(sendMnemoTest->codeMnemo),(int)sendMnemoTest->operStatus);
        }
        else
        {
            unsigned char X = 2;
            emit datasent1(QString(sendMnemoTest->codeMnemo),(int)X);
           // ui->log->append("Status 2");
        }

    }


}
UdpClient::~UdpClient()
{
    delete ui;
    m_pudp->close();
    m_pudp->disconnectFromHost();
}

void UdpClient::on_disconnect_clicked()
{

     if (m_pudp->isOpen())
     {
          ui->log->append("Порт уже открыт!");
           m_pudp->close();
           m_pudp->disconnectFromHost();
           ui->log->append("Порт закрыт!");
           ui->log->append("Соединение разорвано!");
     }
     else
     {
          ui->log->append("Порт уже закрыт!");
     }


}

void UdpClient::on_connect_clicked()
{
    ui->log->append("Попытка подключения!");
    bool *ok;
    int port =  ui->lineEdit->text().toInt(ok,port);
    if (ok)
    {
        ui->log->append("Порт корректен подключения!");
        ui->log->append(QString(port));
        if (m_pudp->isOpen())
        {
           m_pudp->close();
            m_pudp->disconnectFromHost();
        }
        bool rez = m_pudp->bind(port);
          qDebug()<<m_pudp->errorString();
        if (!rez)
        {
            qWarning("Port  %i can't be open", port);
            ui->log->append("Port "+ui->lineEdit->text()+ " can't be open");
        }
        else
            qWarning("Port %i is open!", 8554);
        ui->log->append("Port  "+ui->lineEdit->text()+"  is open");
    }
    else
        {
        ui->log->append("Error Port "+ui->lineEdit->text()+ " can't be open");
        }
}
