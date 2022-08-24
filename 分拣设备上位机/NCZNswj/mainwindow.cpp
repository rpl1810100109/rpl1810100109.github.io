#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("能诚智能");



    /*************初始化参数******************/
    mServer = new QTcpServer();
    pool = QThreadPool::globalInstance(); //得到线程池对象
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_send_clicked()
{

}

int MainWindow::bindServer(int port)
{

    int result = mServer->listen(QHostAddress::Any,port); //将绑定监听的结果存入临时变量中

    connect(mServer,&QTcpServer::newConnection,this,[=](){
    //开启新线程，将套接字丢进去
     QTcpSocket* socket = mServer->nextPendingConnection();
     dealwith = new DealWithDate(socket); //将套接字对象传入数据处理类
     dealwith->setAutoDelete(true); //设置线程自动回收
     pool->start(dealwith);//开启线程
    });

    return result;
}


