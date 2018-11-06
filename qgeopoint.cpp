#include "qgeopoint.h"

/*************************************************
 *  @brief QGeoPoint 类的无参构造函数
 *************************************************/
QGeoPoint::QGeoPoint()
{
    this->x = 0;
    this->y = 0;
}

/*************************************************
 *  @brief QGeoPoint 类的有参构造函数
 *  @param x   横坐标
 *  @param y   纵坐标
 *************************************************/
QGeoPoint::QGeoPoint(float x, float y)
{
    this->x = x;
    this->y = y;
}

/*************************************************
 *  @brief 设置点要素的坐标
 *  @param x   横坐标
 *  @param y   纵坐标
 *************************************************/
void QGeoPoint::setCoordinate(float x, float y)
{
    this->x = x;
    this->y = y;
}
