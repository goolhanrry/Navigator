#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgeomap.h"
#include "mapwidget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked()
{
    // 打开模式对话框，选择文件
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "/", "*.e00");

    // 文件格式校验
    if (fileName.section('.', -1) == "e00")
    {
        // 读取文件并解码
        QGeoMap *map = new QGeoMap(this);
        if (map->loadMap(fileName.toStdString()))
        {
            // 渲染图形
            ui->mapWidget->setPolyline(map->polyline);
            ui->mapWidget->setBoundary(map->maxX, map->minX, map->maxY, map->minY);
            ui->mapWidget->resetOffset();
            ui->mapWidget->update();
        }
        else
        {
            delete map;
        }
    }
    else if (fileName.length())
    {
        QMessageBox::critical(this, "File type error", "Please choose a \".e00\" file", QMessageBox::Yes);
    }
}
