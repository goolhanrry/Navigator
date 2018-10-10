#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QApplication>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include "qpolyline.h"
using namespace std;

class MapWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  explicit MapWidget(QWidget *parent = nullptr);
  ~MapWidget() Q_DECL_OVERRIDE;

  void initializeGL() Q_DECL_OVERRIDE;
  void resizeGL(int width, int height) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;

  void setPolyline(vector<QPolyline *> polyline);
  void setBoundary(float maxX, float minX, float maxY, float minY);
  void resetOffset();

  QWidget *parent;

private:
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;   // 鼠标按下
  void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE; // 鼠标抬起
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;    // 鼠标移动
  void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;        // 滚轮滑动

  vector<QPolyline *> polyline;
  float dX, dY, mX, mY, scale = 0.9;
  QCursor cursor;                                                                  // 光标形状
  double mouseX, mouseY, offsetX = 0, offsetY = 0, newOffsetX = 0, newOffsetY = 0; // 鼠标及图像偏移量

signals:

public slots:
};

#endif // MAPWIDGET_H
