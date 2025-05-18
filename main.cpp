#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.addItem("Цукор",2,32.99);
    w.addItem("Шоколад",1,50);
    w.updateReceiptAmount();
    w.show();
    return a.exec();
}
