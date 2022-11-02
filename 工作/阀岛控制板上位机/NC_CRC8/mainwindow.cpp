#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("能诚智能装备阀岛助手");
    this->setWindowIcon(QIcon(":/beef.ico"));
    this->setFixedSize(699,417); //窗口不可拉伸
    //quint8 addr[7] = {0x01,0x02,0x03,0x04,0x05,0x06,0x04};
    //quint8 resoult = crc8(addr,7);
    //qDebug()<<"格式化16进制小写输出"<<QString().sprintf("%02X",crc8(addr,7));
    //ui->textBrowser->setText(QString().sprintf("%02X",crc8(addr,7)));

    //初始化
    Polynomial = 0x07;
    InitialValue = 0x00;
    XORValue = 0x00;
    //ui->page->setWindowRole("CRC校验");

    connect(ui->menu,&QMenu::aboutToShow, this, &MainWindow::setPage);
    connect(ui->menuCRC,&QMenu::aboutToShow, this, &MainWindow::setPage0);
    connect(ui->menu_2,&QMenu::aboutToShow, this, &MainWindow::on_pushButton_2_clicked);
    connect(ui->DecEdit,&QLineEdit::textEdited,this,&MainWindow::changeDec);
    connect(ui->BinEdit,&QLineEdit::textEdited,this,&MainWindow::changeBin);
    connect(ui->HexEdit,&QLineEdit::textEdited,this,&MainWindow::changeHex);
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=](){
       control* cn = new control();
       cn->show();
    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief CRC 校验，校验值为 8 位
 *
 * @param addr     数据首地址
 * @param num      数据长度（字节）
 * @param type     CRC8 的算法类型
 * @return u8      8 位校验值
 */
 quint8  MainWindow::crc8(quint8* addr, int num)
{
    quint8  data;
    quint8  crc = InitialValue; //初始值
    int i;
    for (; num > 0; num--)
    {
        data = *(addr++);
        //是否反转
//        if (0)
//        {
//            //data = reverse8(data);
//        }
        //与crc初始值异或
        crc = crc ^ data;
        for (i = 0; i < 8; i++)
        {
            //左移移出的位为1，左移后与多项式异或
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ Polynomial;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    //满足条件，反转
//    if (type.OutputReverse == TRUE)
//    {
//        crc = reverse8(crc);
//    }
    crc = crc ^ XORValue; //最后返与结果异或值异或
    return (crc);            //返回最终校验值
}

void MainWindow::on_pushButton_clicked()
{

//    bool ok; //转换成功标志
//    QString st =  ui->lineEdit->text().remove(QRegExp("\\s")); //将输入框内数据切片
//    //循环将字符串数组转化为quin8类型的 并将值转换为16进制数值
//    for ( int i =0;i<st.length();i++)
//    {
//    date[i] =  (quint8)st.mid(i*2, 2).toInt(&ok, 16);
//    }
    //qDebug()<<st;
    //qDebug()<< date[2];
    quint8 resoult = crc8(date,leng);
    ui->textBrowser->setText(QString().sprintf("%02X",resoult));

}

void MainWindow::on_PolynomialInput_currentIndexChanged(int index)
{
    if (index == 0)
        Polynomial = 0x07;
    else
        Polynomial = 0x31;
}

void MainWindow::on_InitialValue_currentIndexChanged(int index)
{
    if (index == 0)
        InitialValue = 0x00;
    else
        InitialValue = 0xff;
}

void MainWindow::on_XORValue_currentIndexChanged(int index)
{
    if (index == 0)
        XORValue = 0x00;
    else
        XORValue = 0xff;
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox MBox;
    MBox.setWindowTitle("关于能诚智能装备有限公司");
    MBox.setText("    能诚智能装备有限公司是一家以***为主体的物流设备生产、加工、服务有限公司，"
                 "公司地址******"
                 "联系方式：***********");
    MBox.setIconPixmap(QPixmap("C:\\Users\\xiexuewu\\Desktop\\icon_c.png"));
    MBox.addButton(QMessageBox::Ok);
    MBox.exec();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    bool ok; //转换成功标志
    QString st =  ui->lineEdit->text().remove(QRegExp("\\s")); //读取输入框内数据，并去除所有空格
    //循环将字符串数组转化为quin8类型的 并将值转换为16进制数值
    for ( int i =0;i<st.length()/2;i++)
    {
    date[i] =  (quint8)st.mid(i*2, 2).toInt(&ok, 16);
    }
    leng = st.length()/2;
}
void MainWindow::setPage()
{

    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::setPage0()
{

    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::changeBin()
{
      bool ok;
    int dateBin =  ui->BinEdit->text().toInt(&ok,2);
    ui->DecEdit->setText(QString("%1").arg(dateBin,3,10,QChar('0')));
    ui->HexEdit->setText(QString("%1").arg(dateBin,2,16,QChar('0')).toUpper());

}
void MainWindow::changeDec()
{
 // bool ok;
 int dateDec =  ui->DecEdit->text().toInt();
 ui->BinEdit->setText(QString("%1").arg(dateDec,8,2,QChar('0')));
 ui->HexEdit->setText(QString("%1").arg(dateDec,2,16,QChar('0')).toUpper());
}
void MainWindow::changeHex()
{
    bool ok;
    int dateHex =  ui->HexEdit->text().toInt(&ok,16);
    ui->BinEdit->setText(QString("%1").arg(dateHex,8,2,QChar('0')));
    ui->DecEdit->setText(QString("%1").arg(dateHex));
}
