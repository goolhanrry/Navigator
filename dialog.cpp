#include <QMessageBox>
#include <sstream>
#include "dialog.h"
#include "ui_dialog.h"

/*************************************************
 *  @brief Dialog 类的构造函数
 *  @param map 指向 QGeoMap 对象的指针
 *************************************************/
Dialog::Dialog(QGeoMap *map) : ui(new Ui::Dialog)
{
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

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

/*************************************************
 *  @brief Dialog 类的析构函数
 *************************************************/
Dialog::~Dialog()
{
    delete ui;
}

/*************************************************
 *  @brief 按钮框点击事件
 *************************************************/
void Dialog::on_buttonBox_accepted()
{
    int FNode = ui->FNodeLineEdit->text().toInt();
    int TNode = ui->TNodeLineEdit->text().toInt();

    // 输入合法性校验
    if (!FNode && !TNode)
    {
        return;
    }
    else if (FNode < 1 || TNode > maxNode || TNode < 1 || FNode > maxNode)
    {
        QMessageBox::critical(this, "Error", "Bad input", QMessageBox::Yes);
        return;
    }

    // 清除结点列表
    map->openList.clear();
    map->closedList.clear();
    map->highlightPolyline.clear();

    // 执行最短路径分析
    map->searchPath(FNode, TNode);
}
