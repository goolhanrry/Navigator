#ifndef QGEOMAP_H
#define QGEOMAP_H

#include <QtWidgets>
#include <vector>
#include <ext/hash_map>
#include "qgeopoint.h"
#include "qgeopolyline.h"
using namespace std;
using namespace __gnu_cxx;

struct Node
{
  int id, index, polylineId; // 结点 ID, 结点索引, 折线 ID
  float F;                   // 结点 F 值

  // 重载 == 操作符以实现查找功能
  bool operator==(const int &id) const
  {
    return this->id == id;
  }

  bool operator==(const pair<int, int> &node) const
  {
    return (this->id == node.first && this->polylineId == node.second);
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

  vector<QGeoPolyline *> polyline, highlightPolyline;
  hash_map<int, QGeoPoint *> nodeList;  // 所有结点无序哈希表
  vector<Node> openList, closedList;    // 相邻结点与已检测结点有序列表
  float maxX, minX, maxY, minY, length; // 地图边界坐标, 路径总长度

protected:
  void switchFile(ifstream *fs, string fileName, int fileIndex);

private:
  void getAdjacentNode(int TNode, int &count);
  void getNearestNode(int &index);
  void generatePath();

  QWidget *parent; // 指向父窗体的指针，用于捕获到异常时弹窗提示

signals:
  void pathUpdated(QString path);
};

#endif // QGEOMAP_H
