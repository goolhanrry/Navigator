#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
using namespace std;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_openFileButton_clicked();
  void on_analyzeButton_clicked();

private:
  Ui::MainWindow *ui;
  QString path; // 上次打开文件的路径
};

#endif // MAINWINDOW_H
