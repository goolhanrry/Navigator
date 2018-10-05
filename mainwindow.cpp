#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedecoder.h"
#include "mapwidget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <string>

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
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "../../../", "*.e00");

    if (fileName.length())
    {
        // 读取文件并解码
        FileDecoder *fileDecoder = new FileDecoder(fileName.toStdString());
        if (fileDecoder->decodeFile())
        {
            // 渲染图形
            ui->mapWidget->setPolyline(fileDecoder->polyline, fileDecoder->size);
            ui->mapWidget->setBoundary(fileDecoder->maxX, fileDecoder->minX, fileDecoder->maxY, fileDecoder->minY);
            ui->mapWidget->update();
        }
    }
}
