#include "mainwindow.h"

#include <QApplication>
#include<QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

   //a.connect(w.mtcp->mSocket,&MyTCP::sigDate,w,&MainWindow::declDate);
    return a.exec();
}
