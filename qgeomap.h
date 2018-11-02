#ifndef QGEOMAP_H
#define QGEOMAP_H

#include <QtWidgets>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "qgeopoint.h"
#include "qgeopolyline.h"
using namespace std;

struct Node
{
  int id, index; // 结点 ID, 结点索引
  float F;       // 结点 F 值

  bool operator==(const int id) const // 重载 == 操作符以实现查找功能
  {
    return this->id == id;
  }
};

class QGeoMap : public QObject
{
  Q_OBJECT

public:
  explicit QGeoMap(QWidget *parent);
  ~QGeoMap();

  bool loadMap(string fileName);
  void searchPath(int FNode, int TNode);

  vector<QGeoPolyline *> polyline;
  map<int, QGeoPoint> nodeList;         // 总结点无序列表
  vector<Node> openList;                // 相邻结点有序列表
  vector<int> closedList;               // 已检测结点有序列表
  float maxX, minX, maxY, minY, length; // 地图边界坐标, 路径总长度

protected:
  void switchFile(ifstream *fs, string fileName, int fileIndex);

private:
  bool getAdjacentNode(int &currentNode, int TNode, int &count);

  QWidget *parent; // 指向父窗体的指针，用于捕获到异常时弹窗提示

signals:
  void pathUpdated(QString path);
};

#endif // QGEOMAP_H
