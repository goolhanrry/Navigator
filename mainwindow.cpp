#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapwidget.h"
#include "dialog.h"
using namespace std;

MainWindow::MainWindow() : ui(new Ui::MainWindow)
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
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", path, "*.e00");

    // 保存上次打开的目录
    path = fileName.section('/', -2);

    // 文件格式校验
    if (fileName.section('.', -1) == "e00")
    {
        // 读取文件并解码
        map = new QGeoMap(this);
        if (map->loadMap(fileName.toStdString()))
        {
            hasMap = true;

            // 更新标题栏文字
            this->setWindowTitle(fileName.section('/', -1) + " - Navigator++");

            // 渲染图形
            ui->mapWidget->setPolyline(map->polyline);
            ui->mapWidget->setBoundary(map->maxX, map->minX, map->maxY, map->minY);
            ui->mapWidget->resetOffset();
            ui->mapWidget->update();
        }
        else
        {
            hasMap = false;

            // 释放无用内存
            delete map;
        }
    }
    else if (fileName.length())
    {
        QMessageBox::critical(this, "Error", "Please choose a \".e00\" file", QMessageBox::Yes);
    }
}

void MainWindow::on_analyzeButton_clicked()
{
    if (hasMap)
    {
        Dialog dialog(map);
        dialog.exec();
    }
    else
    {
        QMessageBox::information(this, "Notice", "Please open a file first", QMessageBox::Yes);
    }
}
