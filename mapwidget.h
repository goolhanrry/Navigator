#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class MapWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  explicit MapWidget(QWidget *parent = nullptr);
  ~MapWidget() Q_DECL_OVERRIDE;

  void initializeGL() Q_DECL_OVERRIDE;
  void resizeGL(int width, int height) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;

  QWidget *parent;

signals:

public slots:
};

#endif // MAPWIDGET_H
