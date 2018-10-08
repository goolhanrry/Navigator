#ifndef QPOLYLINE_H
#define QPOLYLINE_H

#include <string>
#include "qgeopoint.h"
using namespace std;

class QPolyline
{
public:
  QPolyline(string index, int size);

  void addPoint(float x, float y);

  string index;
  int size, count = 0;
  QGeoPoint *pts;
};

#endif // QPOLYLINE_H
