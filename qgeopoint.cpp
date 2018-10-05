#include "qgeopoint.h"

QGeoPoint::QGeoPoint() {}

void QGeoPoint::setCoordinate(float x, float y)
{
    this->x = x;
    this->y = y;
}
