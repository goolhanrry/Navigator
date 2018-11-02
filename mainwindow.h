#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qgeomap.h"
using namespace std;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow();
  ~MainWindow();

private slots:
  void on_openFileButton_clicked();
  void on_analyzeButton_clicked();
  void on_pathUpdated(QString path);

private:
  Ui::MainWindow *ui;
  QGeoMap *map;
  QString path = "/";  // 上次打开文件的路径
  bool hasMap = false; // 是否已打开地图文件
};

#endif // MAINWINDOW_H
