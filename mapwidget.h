#ifndef MAPWIDGET_H
#define MAPWIDGET_H

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

  QWidget *parent;
  float maxX, minX, maxY, minY;

private:
  vector<QPolyline *> polyline;
  int size = 0;

signals:

public slots:
};

#endif // MAPWIDGET_H
