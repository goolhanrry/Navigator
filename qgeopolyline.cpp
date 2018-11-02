#include <math.h>
#include "qgeopolyline.h"

QGeoPolyline::QGeoPolyline(int index, int FNode, int TNode, int size)
{
    this->index = index;
    this->FNode = FNode;
    this->TNode = TNode;
    this->size = size;
    pts = new QGeoPoint[size];
}

QGeoPolyline::~QGeoPolyline()
{
    // 释放点要素所占的内存
    delete[] pts;
    pts = nullptr;
}

/*************************************************
 *  @brief 添加点要素并更新折线长度
 *  @param x  横坐标
 *  @param y  纵坐标
 *************************************************/
void QGeoPolyline::addPoint(float x, float y)
{
    pts[count].setCoordinate(x, y);
    count++;

    if (count > 1)
    {
        length += sqrt(pow(pts[count - 2].x - x, 2) + pow(pts[count - 2].y - y, 2));
    }
}
