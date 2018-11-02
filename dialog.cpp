#include <QMessageBox>
#include <sstream>
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QGeoMap *map) : ui(new Ui::Dialog)
{
    stringstream stream;
    string maxNodeStr;

    this->map = map;
    this->maxNode = map->nodeList.size();

    ui->setupUi(this);

    stream << maxNode;
    stream >> maxNodeStr;

    // 固定对话框尺寸
    setFixedSize(width(), height());
    // 显示可输入结点的范围
    ui->rangeLabel->setText("Please input node ID (1 ~ " + QString::fromStdString(maxNodeStr) + ")");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    int FNode = ui->FNodeLineEdit->text().toInt();
    int TNode = ui->TNodeLineEdit->text().toInt();

    // 输入合法性校验
    if (!FNode && !TNode)
    {
        return;
    }
    else if (!FNode || !TNode || FNode < 1 || TNode > maxNode || FNode < 1 || TNode > maxNode)
    {
        QMessageBox::critical(this, "Error", "Bad input", QMessageBox::Yes);
        return;
    }

    // 清除结点列表
    //map->openList.clear();
    //map->closedList.clear();

    // 执行最短路径分析
    //map->getShortestPath(FNode, TNode);
}
