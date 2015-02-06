#include "udpclient.h"
#include "ui_udpclient.h"

UdpClient::UdpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UdpClient)
{
    ui->setupUi(this);
    //setWindowTitle("UdpClient");
    m_pudp = new QUdpSocket;
    bool rez =m_pudp->bind(4372);
    qDebug()<<m_pudp->errorString();
    //append("Received:"+dateTime.toString());
    if (!rez)
    {
        qWarning("Port  %i can't be open", 4372);
        ui->log->append("Port "+ui->lineEdit->text()+ " can't be open");
    }
    else
        qWarning("Port %i is open!", 4372);
    ui->log->append("Port  "+ui->lineEdit->text()+"  is open");
    connect(m_pudp,SIGNAL(readyRead()),SLOT(slotProcessDatagrams()));
}

void UdpClient::slotProcessDatagrams()
{
    while (m_pudp->hasPendingDatagrams()) {
        qDebug()<<"************************************************************************************************************";
        qDebug()<<"hasPendingDatagrams";
        qDebug()<<(m_pudp->pendingDatagramSize());
        QByteArray baDatagram;
        baDatagram.resize(m_pudp->pendingDatagramSize());
        m_pudp->readDatagram(baDatagram.data(), baDatagram.size());
        // m_datagram.append(baDatagram);
        asupMnenoTest * sendMnemoTest = (asupMnenoTest*)baDatagram.data();
        sendMnemoTest->marker[5]='\0';
        ui->log->append("##################    Принят пакет    #######################");
        char str[2056];
        int i, n = 0;
        for(i = 0; i < baDatagram.size();)
        {
            n += sprintf(str+n, "%02x", (unsigned char) baDatagram[i++]);
            str[n++] = ' ';
        }
        str[--n] = '\0';
        qDebug() <<"str = "<<str;
        ui->log->append("###################    Код пакета    ########################");
        ui->log->append(QString(str));
        ui->log->append("#################  Расшифровка пакета  ######################");
        ui->log->append("marker = "+  QString(sendMnemoTest->marker));
        ui->log->append("--------------------------------------------------------");
        ui->log->append("operStatus = "+ QString::number(sendMnemoTest->operStatus));
        ui->log->append("--------------------------------------------------------");
         int cod = (int) sendMnemoTest->codoper; //unsigned int cod = -256;
         ui->log->append("codoper = "+ QString::number(sendMnemoTest->codoper)+"("+QString::number(cod)+")");
        ui->log->append("--------------------------------------------------------");
        ui->log->append("codeMnemo = "+ QString(sendMnemoTest->codeMnemo));
        ui->log->append("--------------------------------------------------------");
        ui->log->append("nameLenth = "+ QString::number(sendMnemoTest->nameLenth));
        ui->log->append("--------------------------------------------------------");
        if (cod>=0)
        {
            emit datasent1(QString(sendMnemoTest->codeMnemo),(int)sendMnemoTest->operStatus);
        }
        else
        {
            unsigned char X = 2;
            emit datasent1(QString(sendMnemoTest->codeMnemo),(int)X);
        }
        //emit m_pudp->readyRead();
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
    m_pudp->disconnectFromHost();
    ui->log->append("Порт закрыт!");
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
    int port = 4372;
    port = ui->lineEdit->text().toInt();
    if (port)
    {
        ui->log->append("Порт корректен подключения!");
        ui->log->append(QString(port));
        m_pudp->disconnectFromHost();
        bool rez = m_pudp->bind(port);
        qDebug()<<m_pudp->errorString();
        if (!rez)
        {
            qWarning("Port  %i can't be open", port);
            ui->log->append("Port "+ui->lineEdit->text()+ " can't be open");
        }
        else
            qWarning("Port %i is open!", port);
        ui->log->append("Port  "+ui->lineEdit->text()+"  is open");
    }
    else
    {
        ui->log->append("Error Port "+ui->lineEdit->text()+ " can't be open");
    }
}



void UdpClient::on_clean_clicked()
{
    ui->log->clear();
}

void UdpClient::on_showCod_clicked()
{

}
