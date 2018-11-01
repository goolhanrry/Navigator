#ifndef QGEOPOINT_H
#define QGEOPOINT_H

class QGeoPoint
{
public:
  explicit QGeoPoint();

  void setIndex(int index);
  void setCoordinate(float x, float y);

  int index;
  float x, y;
};

#endif // QGEOPOINT_H
