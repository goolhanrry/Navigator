#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // 开启高 DPI 支持
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
