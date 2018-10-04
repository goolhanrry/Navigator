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

    // 读取文件并解码
    FileDecoder *fileDecoder = new FileDecoder(fileName.toStdString());
    fileDecoder->decodeFile();
}
