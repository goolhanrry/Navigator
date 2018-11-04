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
  void resizeEvent(QResizeEvent *size);
  void on_openFileButton_clicked();
  void on_analyzeButton_clicked();
  void on_pathUpdated(QString path);

private:
  Ui::MainWindow *ui;
  QFontMetrics *elidfont;
  QGeoMap *map = nullptr;
  QString path, filePath = "/"; // 路径分析的输出结果, 上次打开文件的路径
};

#endif // MAINWINDOW_H
