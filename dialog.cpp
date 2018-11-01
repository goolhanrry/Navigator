#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // 固定对话框尺寸
    setFixedSize(width(), height());
}

Dialog::~Dialog()
{
    delete ui;
}
