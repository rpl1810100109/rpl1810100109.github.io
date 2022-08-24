#include "mytcp.h"
#include<QTimer>

MyTCP::MyTCP(QObject *parent,QTcpSocket* _mSocket) : QObject(parent)
{
   mSocket = _mSocket;


}

MyTCP::~MyTCP()
{
    /****释放堆区内存，指针指向空****/
      delete  mSocket;
      mSocket = NULL;


}
//void MyTCP::NewConnect()
//{



//    LinkStatu = true;
//    mSocket = mServer->nextPendingConnection();

//    OtherIp = mSocket->peerAddress().toString();
//    OtherPort = mSocket->peerPort();
//    AllSocket.append(mSocket);
//    qDebug()<<OtherIp<<"   "<<OtherPort<<endl;
//    //出现一个连接就设置一个信号槽
//    buffer = mSocket->readAll();
//    QByteArray mydate;
//    mydate.append(120);
//    mydate.append(100);
//    mSocket->write(mydate);
//    qDebug()<<mydate.at(0);
//    sigDate(mydate,OtherIp,OtherPort);
//    connect(mSocket,&QTcpSocket::readyRead,this,[=]()
//    {
//        buffer = mSocket->readAll();


//    });



//    return;
//}
QByteArray MyTCP::RcvDate()
{

    return mSocket->readAll();

}

qint64 MyTCP::sendDate(QByteArray& _date)
{   if(!_date.length()|| mSocket == NULL)
        return -1;

    return mSocket->write(_date);;

}
