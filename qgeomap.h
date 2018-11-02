#ifndef QGEOMAP_H
#define QGEOMAP_H

#include <QtWidgets>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include "qgeopoint.h"
#include "qgeopolyline.h"
using namespace std;

class QGeoMap
{
public:
  explicit QGeoMap(QWidget *parent);
  ~QGeoMap();

  bool loadMap(string fileName);
  void searchPath(int FNode, int TNode);

  vector<QGeoPolyline *> polyline;
  map<int, QGeoPoint> nodeList;         // 总结点列表
  map<int, float> openList;               // 相邻结点列表
  set<int> closedList;                  // 已检测结点列表
  float maxX, minX, maxY, minY, length; // 地图边界坐标, 路径总长度

protected:
  void switchFile(ifstream *fs, string fileName, int fileIndex);

private:
  void getAdjacentNode(int currentNode, int TNode);

  QWidget *parent; // 指向父窗体的指针，用于捕获到异常时弹窗提示
};

#endif // QGEOMAP_H
