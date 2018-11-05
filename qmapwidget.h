#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QApplication>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include "qgeomap.h"
using namespace std;

class QMapWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  explicit QMapWidget(QWidget *parent = nullptr);
  ~QMapWidget() Q_DECL_OVERRIDE;

  void initializeGL() Q_DECL_OVERRIDE;
  void resizeGL(int width, int height) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;

  void setMap(QGeoMap *map);
  void resetOffset();

  QWidget *parent;

private:
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;   // 鼠标按下
  void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE; // 鼠标抬起
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;    // 鼠标移动
  void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;        // 滚轮滑动

  QGeoMap *map = nullptr;
  float dX, dY, mX, mY, scale = 0.9f;
  QCursor cursor;                                                                  // 光标形状
  double mouseX, mouseY, offsetX = 0, offsetY = 0, newOffsetX = 0, newOffsetY = 0; // 鼠标及图像偏移量
};

#endif // MAPWIDGET_H
