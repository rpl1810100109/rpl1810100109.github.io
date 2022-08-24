#ifndef DEALWITHDATE_H
#define DEALWITHDATE_H

#include <QObject>
#include <QRunnable>
#include<QThreadPool>
#include<mytcp.h>
#include<QTcpSocket>

#include <QDebug>
#include <QSqlDatabase>
#include <QStringList>
#include <QSqlError>
#include <QSqlQuery>

class DealWithDate : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit DealWithDate(QObject *parent = nullptr,QTcpSocket *msocket=nullptr);

signals:

private:
    MyTCP* mTcp;            //TCp 通讯对象

/**成员函数**/
public:
    void run() override; //重写父类的虚函数
    QVector<int> ReadDateBase(); //读数据库
    int WriteDateBase(QVector<int> date);//写数据库

/**  成员变量**/
public:
    QTcpSocket* mSocket; //套接字对象

};

#endif // DEALWITHDATE_H
