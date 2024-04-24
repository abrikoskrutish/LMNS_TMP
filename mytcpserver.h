#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <Qvector>
//Хэндлер
//нужно чтобы работал механизм сингалов и слотов
//слоты -- если мы получили какой-то сингал, то другие компоненты
//программы будут что-то выполнять


#include <QTcpServer>
#include <QTcpSocket>
//передача пакетов


#include <QtNetwork>
//подключение констант для сетевого взаимодействия

#include <QByteArray>
//тип побайтовой передачи данных


#include <QDebug>
//Вывод в консполь сообщений

class MyTcpServer : public QObject
{
    Q_OBJECT
    //const которые испольуются в mytcpserver
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
    void mainLogic();
    QByteArray auth(QString log, QString pass);
    QByteArray reg(QString log, QString pass, QString mail);
    QByteArray functionality(QString data_from_client);
    //конструктор и деструктор

public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
    //методы класса, методы которые будут происходить в случае
    //срабатывания сигнала

private:
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    //Qvector <char> alph = {'1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','49','50','51','52','53','54','55','56','57','58','59','60','61','62','63','64','65','66','67','68','69','70','71','72','73','74','75','76','77','78','79','80','81','82','83','84','85','86','87','88','89','90','91','92','93','94','95','96','97','98','99',};
    //если сервер будет многопользовательским, то лучше использовать
    //map
    //int server_status;
};
#endif // MYTCPSERVER_H
