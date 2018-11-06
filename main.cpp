#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // 开启高 DPI 支持
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
