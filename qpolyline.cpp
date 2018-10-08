#include "qpolyline.h"

QPolyline::QPolyline(string index, int size)
{
    this->index = index;
    this->size = size;
    pts = new QGeoPoint[size];
}

void QPolyline::addPoint(float x, float y)
{
    // 若数组已满则返回
    if (count >= size)
    {
        return;
    }

    pts[count].setCoordinate(x, y);
    count++;
}
