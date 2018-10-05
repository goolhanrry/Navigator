#ifndef QPOLYLINE_H
#define QPOLYLINE_H

#include "qgeopoint.h"

class QPolyline
{
public:
  QPolyline();

  void addPoint(float x, float y);
  void setSize(int size);

  int size, count = 0;
  QGeoPoint *pts;
};

#endif // QPOLYLINE_H
