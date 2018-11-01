#include "qgeopoint.h"

QGeoPoint::QGeoPoint() {}

/*************************************************
 *  @brief 设置点要素的索引
 *  @param index 索引值
 *************************************************/
void QGeoPoint::setIndex(int index)
{
    this->index = index;
}

/*************************************************
 *  @brief 设置点要素的坐标
 *  @param x  横坐标
 *  @param y  纵坐标
 *************************************************/
void QGeoPoint::setCoordinate(float x, float y)
{
    this->x = x;
    this->y = y;
}
