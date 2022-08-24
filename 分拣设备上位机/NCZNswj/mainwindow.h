#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mytcp.h>
#include<QString>
#include <QTcpSocket>
#include<QVector>
#include<QTcpServer>
#include<dealwithdate.h>
#include<QThreadPool>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int CloseListen();  //关闭监听
    QThreadPool* pool; //线程池对象
private slots:
    void on_send_clicked();

public:
    DealWithDate* dealwith;


    //绑定监听
    QTcpServer* mServer;                //TCP服务器对象
    int bindServer(int port); //绑定端口IP
    QTcpSocket newConnect();//监听到新的连接时
    QVector<QTcpSocket> socketArry; //socket数组
private:
    Ui::MainWindow *ui;
//    MyTCP *mtcp;
    int port; //端口
    QString ip; //IP

};
#endif // MAINWINDOW_H
