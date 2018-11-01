#include <math.h>
#include "qgeopolyline.h"

QGeoPolyline::QGeoPolyline(int index, int size)
{
    this->index = index;
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
 *  @brief 添加点要素
 *  @param x  横坐标
 *  @param y  纵坐标
 *************************************************/
void QGeoPolyline::addPoint(float x, float y)
{
    // 若数组已满则返回
    if (count >= size)
    {
        return;
    }

    pts[count].setCoordinate(x, y);
    count++;
}

/*************************************************
 *  @brief 添加首尾节点索引并生成折线长度
 *  @param FNode  首节点 ID
 *  @param TNode  尾节点 ID
 *************************************************/
void QGeoPolyline::setNode(int FNode, int TNode)
{
    // 添加首尾节点索引
    pts[0].setIndex(FNode);
    pts[size - 1].setIndex(TNode);

    // 计算折线长度

}
