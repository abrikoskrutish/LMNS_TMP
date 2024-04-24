#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include<QString>
#include <vector>
using namespace std;
MyTcpServer::~MyTcpServer()
{

    mTcpServer->close();
    //server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        //server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    //   if(server_status==1){
    mTcpSocket = mTcpServer->nextPendingConnection();
    mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
    connect(mTcpSocket, &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
    connect(mTcpSocket,&QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);
    // }
}

void MyTcpServer::slotServerRead(){
    QString res = "";
    //строка которую мы получаем от клиента
    while(mTcpSocket->bytesAvailable()>0)
    {
        QByteArray array =mTcpSocket->readAll();
        qDebug()<<array<<"\n";
        if(array=="\x01")
        {
            mTcpSocket->write(functionality(QString(res.toUtf8())));
            res = "";

        }
        else
            res.append(array);
    }
    mTcpSocket->write(functionality(QString(res.toUtf8())));


}

QByteArray MyTcpServer::auth(QString log, QString pass) {
    return "auth had been completed\r\n";
}

QByteArray MyTcpServer::reg(QString log, QString pass, QString mail) {

    return "reg had been completed\r\n";
}

void MyTcpServer::slotClientDisconnected(){
    mTcpSocket->close();
}

QByteArray MyTcpServer::functionality(QString data_from_client) {
    // NameOfFunc&Param1&Param2&Param3 to NameOfFunc(param1,param2,param3)
    QStringList data_from_client_list = data_from_client.split(QLatin1Char('&'));

    if (data_from_client_list.size() < 2) {
        return "error\r\n";
    }

    QString func_name = data_from_client_list.first();
    data_from_client_list.removeFirst();

    if(func_name == "auth") {
        if (data_from_client_list.size() != 2) {
            return "error\r\n";
        }
        return auth(data_from_client_list.at(0), data_from_client_list.at(1));
    }

    else if(func_name == "reg") {
        if (data_from_client_list.size() != 3) {
            return "error\r\n";
        }
        return reg(data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2));
    }

}



