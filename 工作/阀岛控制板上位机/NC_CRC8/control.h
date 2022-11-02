
#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QPushButton>
#include<QMessageBox>
namespace Ui {
class control;
}

class control : public QWidget
{
    Q_OBJECT

public:
    explicit control(QWidget *parent = nullptr);
    ~control();

//普通成员变量
public:
    QTcpServer* mServer;
    QTcpSocket* mSocket; //套接字
    bool ConnectionState;//连接状态




//槽函数
public slots:
    void DealNewConnect();
    void ChangeLocalIp();               //改变控制板ip
    void ChangeRemoteIp();               //改变控制板远端ip
    void ChangeRemotePort();           //改变控制板远端端口
    void ReStartW5100();                //重启w5100
    void WriteAndRestart();            //写入参数并重启
    void ChangeOut();                   //改变电磁阀输出
    void GetOutList();                  //获取电磁阀目前输出状态
    void SetListen();                   //设置监听
    void SetDestroyListen();            //断开连接
//普通成员函数
public:
    /***网络部分****/
    int SendDate(quint8* date,int length);     //发送数据
    int DealrecvDate(); //处理接收的数据

    /*****逻辑处理部分*****/
    quint8 crc8(quint8* addr, int num); //CRC8校验



private:
    Ui::control *ui;
};

#endif // CONTROL_H
