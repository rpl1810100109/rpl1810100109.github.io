#include "dealwithdate.h"

DealWithDate::DealWithDate(QObject *parent,QTcpSocket* msocket)
    : QObject(parent)
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


}
