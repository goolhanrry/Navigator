#ifndef QGEOPOINT_H
#define QGEOPOINT_H

class QGeoPoint
{
public:
  explicit QGeoPoint();
  explicit QGeoPoint(int index, float x, float y);

  void setIndex(int index);
  void setCoordinate(float x, float y);
  bool operator<(const QGeoPoint &p) const; // 重载比较运算符以加速排序

  int index;
  float x, y;
};

#endif // QGEOPOINT_H
