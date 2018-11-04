#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "qgeomap.h"

namespace Ui
{
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

  public:
    explicit Dialog(QGeoMap *map);
    ~Dialog();

  private slots:
    void on_buttonBox_accepted();

  private:
    Ui::Dialog *ui;
    QGeoMap *map; // 指向要进行路径分析的 QGeoMap 对象的指针
    int maxNode;
};

#endif // DIALOG_H
