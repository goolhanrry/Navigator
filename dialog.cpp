#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QGeoMap *map) : ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->map = map;

    // 固定对话框尺寸
    setFixedSize(width(), height());
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    // 清除节点列表
    map->openList.clear();
    map->closedList.clear();

    // 执行最短路径分析
    map->shortestPath(ui->FNodeLineEdit->text().toInt(), ui->TNodeLineEdit->text().toInt());
}
