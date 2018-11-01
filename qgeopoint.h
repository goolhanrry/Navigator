#ifndef QGEOPOINT_H
#define QGEOPOINT_H

class QGeoPoint
{
  public:
    explicit QGeoPoint();

    void setCoordinate(float x, float y);

    float x, y;
};

#endif // QGEOPOINT_H
