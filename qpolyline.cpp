#include "qpolyline.h"

QPolyline::QPolyline(int size)
{
    this->size = size;
    pts = new QPoint[size];
}

void QPolyline::addPoint(int x, int y)
{
    // 若数组已满则返回
    if (count >= size)
    {
        return;
    }

    pts[count].setX(x);
    pts[count].setY(y);
    count++;
}
