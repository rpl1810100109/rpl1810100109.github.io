#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QMessageBox>
#include<control.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//算法枚举
enum Method{
            CRC8,
            CRC16,
            CRC32
 };
//数据反转
enum DataInversion{
        MSB,
        LSB
 };
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     Method method; //校验算法
     quint8 Polynomial;//多项式
     bool dateInversion;  //数据反转
     QString dateType; //数据类型
     quint8  InitialValue;//初始值
     quint8  XORValue;    //异或值
     quint8 date[7]; //数据源
    int leng;

     quint8 crc8(quint8* addr, int num);
private slots:
     void on_pushButton_clicked();

     void on_PolynomialInput_currentIndexChanged(int index);

     void on_InitialValue_currentIndexChanged(int index);

     void on_XORValue_currentIndexChanged(int index);

     void on_pushButton_2_clicked();

     void on_lineEdit_textChanged(const QString &arg1);
     void  setPage(); //点击切换CRC校验页面
     void  setPage0();//点击切换进制转换页面

     //进制转换槽函数
     void changeDec();
     void changeHex();
     void changeBin();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
