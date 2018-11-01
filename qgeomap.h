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
  explicit QGeoMap(QWidget *parent);
  ~QGeoMap();

  bool loadMap(string fileName);

  vector<QGeoPolyline *> polyline;
  float maxX, minX, maxY, minY; // 地图边界坐标

protected:
  void switchFile(ifstream *fs, string fileName, int fileIndex);

  QWidget *parent; // 指向父窗体的指针，用于捕获到异常时弹窗提示
  vector<QGeoPoint *> openList, closedList; // 节点列表
};

#endif // QGEOMAP_H
