#include "control.h"
#include "ui_control.h"

control::control(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::control)
{
    ui->setupUi(this);
    mServer = new QTcpServer();
    mSocket = NULL;
    //mServer->listen(QHostAddress::LocalHost,8088); //绑定监听
    //connect(mServer,&QTcpServer::newConnection,this,&control::DealNewConnect); //处理新的连接请求
    //connect(mSocket,&QTcpSocket::readyRead,this,&control::DealrecvDate); //绑定接收信号处理
    ui->lineEdit_2->setReadOnly(true);
    //操作按钮与逻辑处理函数连接
    connect(ui->IpBtn,&QPushButton::clicked,this,&control::ChangeLocalIp);
    connect(ui->remoteIpBtn,&QPushButton::clicked,this,&control::ChangeRemoteIp);
    connect(ui->remoteportBtn,&QPushButton::clicked,this,&control::ChangeRemotePort);
    connect(ui->PowerOutBtn,&QPushButton::clicked,this,&control::ChangeOut);
    connect(ui->OutValueBtn,&QPushButton::clicked,this,&control::GetOutList);
    connect(ui->SetListen,&QPushButton::clicked,this,&control::SetListen);
    connect(ui->DestroyListen,&QPushButton::clicked,this,&control::SetDestroyListen);

    connect(ui->Restar,&QPushButton::clicked,this,&control::ReStartW5100);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&control::WriteAndRestart);

}

control::~control()
{
    delete ui;
}
void control::SetListen(){


    int res = 0;
    res =  mServer->listen(QHostAddress::AnyIPv4,8088); //绑定监听

    if(res){
         // ui->MyIp->setText();
          ui->SetListen->setEnabled(false);
          ui->DestroyListen->setEnabled(true);

    }
    connect(mServer,&QTcpServer::newConnection,this,&control::DealNewConnect); //处理新的连接请求

}

void control::SetDestroyListen()
{


    if(mSocket != NULL)
        mSocket->disconnectFromHost();
    mServer->close();
    ui->SetListen->setEnabled(true);
    ui->DestroyListen->setEnabled(false);

}




//处理新连接
void control::DealNewConnect()
{
    mSocket = mServer->nextPendingConnection(); //将socket设置为新的连接
    if(mSocket!= NULL){
            ConnectionState = true;
            ui->ConnectState->setText("已连接");

    }

    connect(mSocket,&QTcpSocket::readyRead,this,&control::DealrecvDate); //绑定接收信号处理
    connect(mSocket,&QTcpSocket::disconnected,this,[=](){
        mSocket->close();
        mSocket = NULL;
        ui->ConnectState->setText("未连接");
        QMessageBox::warning(this,"警告","与目标已丢失连接",QMessageBox::Ok);
    });

}

void control::ChangeLocalIp()
{
    quint8 date[8];
    date[0] = 0xA5; //在该部分 前三位为固定值
    date[1] = 0xD1;
    date[2] = 0x04;
    QStringList st;
    st = ui->LocalIp->text().split(".");
    for ( int i =0;i<st.length();i++) {
        date[3+i] = st[i].toInt();
    }
    qDebug()<<st.length();
    date[7] = crc8(date,7); //第八位校验位
        qDebug()<<st.length();
    SendDate(date,8);
}

void control::ChangeRemoteIp()
{
    quint8 date[8];
    date[0] = 0xA5; //在该部分 前三位为固定值
    date[1] = 0xD3;
    date[2] = 0x04;
    QStringList st;
    st = ui->RemoteIp->text().split(".");
    for ( int i =0;i<st.length();i++) {
        date[3+i] = st[i].toInt();
    }
    date[7] = crc8(date,7); //第八位校验位
    SendDate(date,8);
}



void control::ChangeRemotePort()
{
    quint8 date[6];
    date[0] = 0xA5; //在该部分 前三位为固定值
    date[1] = 0xD4;
    date[2] = 0x02;
    QStringList st;
    st = ui->RemotePort->text().split(".");
    for ( int i =0;i<st.length();i++) {
        date[3+i] = st[i].toInt();
    }
    date[5] = crc8(date,5); //第八位校验位
    SendDate(date,6);
}

void control::ReStartW5100()
{
    quint8 date[3];
    date[0] = 0xA5; //在该部分 前三位为固定值
    date[1] = 0xE0;
    date[2] = 0xF7;
    SendDate(date,3);
}

void control::WriteAndRestart()
{
    quint8 date[3];
    date[0] = 0xA5; //在该部分 前三位为固定值
    date[1] = 0xE1;
    date[2] = 0xF0;
    SendDate(date,3);
}

void control::ChangeOut()
{
    quint8 date[20];
    date[0] = 0xA5; //在该部分 前三位为固定值
    date[1] = 0xC2;
    date[2] = 0x02;
    QStringList st;
    st = ui->lineEdit->text().split(",");
    int leng = st.length();

    quint16 buffer = 0x00;
    //qDebug()<<st[1];
    for ( int i =0;i<leng;i++) {    //通过0x01根据数值去左移再相加，得到操作数
        quint16 init = 0x01;
        buffer += (init<<(st[i].toInt()-1));
    }
    quint8 buffer1 = buffer>>8;
    quint8 buffer2 = buffer&0xff;
    date[3] = buffer1;
    date[4] = buffer2;
    date[5] = crc8(date,5); //第八位校验位
    SendDate(date,6);
}

void control::GetOutList()
{
    quint8 date[20];
    //0xA5 0xC3 0x1E
    date[0] = 0xA5; //在该部分 前三位为固定值
    date[1] = 0xC3;
    date[2] = 0x1E;
    SendDate(date,3);
}


int control::SendDate(quint8* date,int length)
{
    int resoult;
    if(mSocket == NULL)
    {
          QMessageBox::warning(this,"警告","网络未连接!请连接成功后操作",QMessageBox::Ok);
          return 0;
    }
    resoult =  mSocket->write((char*)date,length);
    return resoult;
}



//接收数据处理
int control::DealrecvDate()
{
    quint8 date[100];
    bool ok;
    int Datelength;
    QString _date = QString::fromUtf8(mSocket->readAll());
    //qDebug()<<_date;
    QStringList ls = _date.split(" ");
    Datelength = ls.length();
    //qDebug()<<ls;
    for(int i=0;i<Datelength;i++)
    {
        date[i] =  (quint8)ls.at(i).toInt(&ok, 16);
    }
    qDebug()<<date[2];
    //检查校验位
    Datelength = date[2];
    if(date[3+Datelength] != crc8(date,3+Datelength))
    {
        qDebug()<<"未通过校验"<<date[3+Datelength]<<" 校验码  "<< crc8(date,3+Datelength)<< "  "<<3+Datelength;
        return 0;
    }

    //检验功能码
    switch(date[3])
    {
    //case 0xc0:  //心跳包

        //break;
    case 0xC2:  //控制电磁阀输出

        break;

    case 0xC3:  //控制板输出状态读取
    {

       quint16 reDate;
       reDate = date[4];
       reDate = reDate<<8;

       reDate = reDate + date[5];
       //通过左移计算哪一位为1；
       QString resoult;
       for(int i =16; i>0;i--)
       {
        if((reDate & 0x8000) >0){
            resoult.append(QString::number(i));
            resoult.append(",");
        }
        reDate = reDate<<1;
       }
       ui->lineEdit_2->setText(resoult);
      break;
    }
    case 0xD0:  //改变控制板mac地址
        //成功给弹窗通知
        break;
    case 0xD1:  //改变控制板ip


        break;
    case 0xD2:  //改变控制板网关

        break;
    case 0xD3:  //改变远端ip

        break;
    case 0xD4:  //改变远端端口

        break;
    case 0xE0:  //重启w5100

        break;
    case 0xE1:  //写入参数并重启w5100

        break;

    }


    return 0 ;
}

quint8 control::crc8(quint8 *addr, int num)
{
    quint8  data;
    quint8  crc = 0x00; //初始值
    int i;
    for (; num > 0; num--)
    {
        data = *(addr++);
        crc = crc ^ data;
        for (i = 0; i < 8; i++)
        {
            //左移移出的位为1，左移后与多项式异或
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ 0x07;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return (crc);            //返回最终校验值
}
