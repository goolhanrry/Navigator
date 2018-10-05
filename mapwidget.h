#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "qpolyline.h"

class MapWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  explicit MapWidget(QWidget *parent = nullptr);
  ~MapWidget() Q_DECL_OVERRIDE;

  void initializeGL() Q_DECL_OVERRIDE;
  void resizeGL(int width, int height) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;

  void setPolyline(QPolyline *polyline, int size);
  void setBoundary(float maxX, float minX, float maxY, float minY);

  QWidget *parent;
  float maxX = 1, minX = -1, maxY = 1, minY = -1;

private:
  QPolyline *polyline;
  int size;

signals:

public slots:
};

#endif // MAPWIDGET_H
