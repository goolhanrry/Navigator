#ifndef QGEOPOLYLINE_H
#define QGEOPOLYLINE_H

#include <string>
#include "qgeopoint.h"
using namespace std;

class QGeoPolyline
{
public:
  explicit QGeoPolyline(int index, int FNode, int TNode, int size);
  ~QGeoPolyline();

  void addPoint(float x, float y);

  int index, FNode, TNode, size, count = 0;
  float length = 0; // 折线当前长度
  QGeoPoint *pts;   // 折线包含的点集
};

#endif // QGEOPOLYLINE_H
