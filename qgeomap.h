#ifndef QGEOMAP_H
#define QGEOMAP_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "mainwindow.h"
#include "qgeopolyline.h"
using namespace std;

class QGeoMap
{
public:
  QGeoMap(QWidget *parent);
  ~QGeoMap();

  bool loadMap(string fileName); // 从 e00 文件中读取地图数据

  vector<QGeoPolyline *> polyline;
  float maxX, minX, maxY, minY; // 地图边界坐标

protected:
  void switchFile(ifstream *fs, string fileName, int fileIndex);

  QWidget *parent; // 指向父窗体的指针，用于捕获到异常时弹窗提示
};

#endif // QGEOMAP_H
