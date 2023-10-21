#include "dealwithdate.h"


/**冒号后面为派生类调用基类构造函数**/
DealWithDate::DealWithDate(QWidget *parent,QTcpSocket* msocket)
    :DateBase(parent),MyTCP(msocket)
{

    mSocket = msocket; //初始化套接字


}

void DealWithDate::run()
{
    //在run函数中绑定各种信号
    /*****
     *
      1.有数据接收
      2.对方断开连接
      3.心跳监测
      4.发送数据（两种选择：在接收数据并且在数据库查询之后直接发送，或者查询完毕之后发送一个信号去触发发送。第二种耦合性更低）
    **/
    connect(mSocket,&QTcpSocket::readyRead,mTcp,&MyTCP::RcvDate); //接收数据存入数据缓冲区
    connect(mTcp,&MyTCP::PleaseDeal,this,&DealWithDate::ReadDateBase); //使用接受缓冲区的数据去读取数据库


}
