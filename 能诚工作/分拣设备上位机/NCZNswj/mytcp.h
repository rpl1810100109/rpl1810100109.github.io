#ifndef MYTCP_H
#define MYTCP_H

#include <QObject>
#include<QByteArray>
#include<QTcpSocket>
#include<QTcpServer>
#include <QString>
#include<QVector>
class MyTCP
{
public:
    explicit MyTCP(QTcpSocket* _mSocket= nullptr); //构造函数
    ~MyTCP();                                   //析构函数

signals:
    void sigDate(QByteArray date,QString ip,qint16 port);
    void PleaseDeal(QByteArray buffer);

public:

    QTcpSocket* mSocket;
    QString OtherIp ;
    qint16 OtherPort;
    bool LinkStatu = false;


public:
   // bool setPort(); //设置端口,应在Master中
    qint64 sendDate(QByteArray& _date);         //发送数据
    QByteArray RcvDate();                  //接收数据
    //QTcpSocket& newConnection();             //处理新的连接时(开启子线程)应在Master中
    int MyListen();                         //绑定监听
    int CloseSocket(QTcpSocket& socket);    //关闭套接字



private:
    int port = 8081; //端口默认为8081
//    QTcpSocket* mSocket;
//    QTcpServer* mServer;
  //  QVector<QTcpSocket*> AllSocket; //套接字数组，应存放于Master中
    QByteArray buffer;                  //发送缓冲区

};

#endif // MYTCP_H
