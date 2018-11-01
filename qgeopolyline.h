#ifndef QGEOPOLYLINE_H
#define QGEOPOLYLINE_H

#include <string>
#include "qgeopoint.h"
using namespace std;

class QGeoPolyline
{
public:
  explicit QGeoPolyline(int index, int size);
  ~QGeoPolyline();

  void addPoint(float x, float y);
  void setNode(int FNode, int TNode);

  int index, size, count = 0;
  QGeoPoint *pts;
};

#endif // QGEOPOLYLINE_H
