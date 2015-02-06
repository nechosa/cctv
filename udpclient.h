#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QWidget>
#include <QTextEdit>
#include <QUdpSocket>

/*
Класс клиента
Принимает пакеты на порт 8554
*/

namespace Ui {
class UdpClient;
}


class UdpClient : public QWidget
{
    Q_OBJECT
    
private:
    QUdpSocket* m_pudp;

public:
    explicit UdpClient(QWidget *parent = 0);
    void sendSignal()
    {
        emit datasent("Information");
    }
    ~UdpClient();
#pragma pack(1)
    struct asupMnenoTest {
        char marker[5];//Заголовок пакета ASUPP
        unsigned int codoper;//Код операции 2 байта
        unsigned char operStatus;//Статус оперции 0-начата;1-завершена;2-вручную
        unsigned char nameLenth;//Длина строки
        const char codeMnemo[]; //имя мнемосхемы
    };
#pragma pack()
    
private:
    Ui::UdpClient *ui;

private slots:
    void slotProcessDatagrams();
    void on_disconnect_clicked();
    void on_connect_clicked();


    void on_clean_clicked();

    void on_showCod_clicked();

signals:
    void datasent(const QString);
    void datasent1(const QString, unsigned int);
};

#endif // UDPCLIENT_H
