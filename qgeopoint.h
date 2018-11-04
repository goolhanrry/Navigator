#ifndef QGEOPOINT_H
#define QGEOPOINT_H

class QGeoPoint
{
public:
  explicit QGeoPoint();
  explicit QGeoPoint(float x, float y);

  void setCoordinate(float x, float y);

  float x, y;
};

#endif // QGEOPOINT_H
