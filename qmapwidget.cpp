#include <glu.h>
#include "qmapwidget.h"
using namespace std;

/*************************************************
 *  @brief QMapWidget 类的构造函数
 *  @param parent 指向父组件的指针
 *************************************************/
QMapWidget::QMapWidget(QWidget *parent)
{
    this->parent = parent;
    cursor.setShape(Qt::OpenHandCursor);
}

/*************************************************
 *  @brief QMapWidget 类的析构函数
 *************************************************/
QMapWidget::~QMapWidget()
{
    // 指向 centralWidget 的指针置空，其内存交由系统释放
    parent = nullptr;
}

/*************************************************
 *  @brief OpenGL 初始化事件
 *************************************************/
void QMapWidget::initializeGL()
{
    // 初始化 OpenGL 函数
    initializeOpenGLFunctions();

    // 全局背景色
    glClearColor(0.13f, 0.15f, 0.18f, 0);
}

/*************************************************
 *  @brief QMapWidget 组件大小改变事件
 *************************************************/
void QMapWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

/*************************************************
 *  @brief QMapWidget 组件重绘事件
 *************************************************/
void QMapWidget::paintGL()
{
    // 若无地图对象则返回
    if (map == nullptr)
    {
        return;
    }

    // 清空画布
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 刷新相机视角
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(offsetX + newOffsetX, offsetY + newOffsetY, 0);

    // 绘制图形
    if (this->width() * dY >= this->height() * dX)
    {
        glColor3f(1, 0.8f, 0);
        for (QGeoPolyline *item : map->polyline)
        {
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < item->size; i++)
            {
                glVertex2f(2 * scale * (item->pts[i].x - mX) * this->height() / (dY * this->width()), 2 * scale * (item->pts[i].y - mY) / dY);
            }
            glEnd();
        }

        if (!map->highlightPolyline.empty())
        {
            glColor3f(0, 1, 0.78f);
            for (QGeoPolyline *item : map->highlightPolyline)
            {
                glBegin(GL_LINE_STRIP);
                for (int i = 0; i < item->size; i++)
                {
                    glVertex2f(2 * scale * (item->pts[i].x - mX) * this->height() / (dY * this->width()), 2 * scale * (item->pts[i].y - mY) / dY);
                }
                glEnd();
            }
        }
    }
    else
    {
        glColor3f(1, 0.8f, 0);
        for (QGeoPolyline *item : map->polyline)
        {
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < item->size; i++)
            {
                glVertex2f(2 * scale * (item->pts[i].x - mX) / dX, 2 * scale * (item->pts[i].y - mY) * this->width() / (dX * this->height()));
            }
            glEnd();
        }

        if (!map->highlightPolyline.empty())
        {
            glColor3f(0, 1, 0.78f);
            for (QGeoPolyline *item : map->highlightPolyline)
            {
                glBegin(GL_LINE_STRIP);
                for (int i = 0; i < item->size; i++)
                {
                    glVertex2f(2 * scale * (item->pts[i].x - mX) / dX, 2 * scale * (item->pts[i].y - mY) * this->width() / (dX * this->height()));
                }
                glEnd();
            }
        }
    }
}

/*************************************************
 *  @brief 设置 QOpenGLWidget 组件要绘制的地图
 *  @param map     指向 QGeoMap 类的指针
 *************************************************/
void QMapWidget::setMap(QGeoMap *map)
{
    this->map = map;

    // 绘图数据初始化
    dX = map->maxX - map->minX;
    dY = map->maxY - map->minY;
    mX = dX / 2 + map->minX;
    mY = dY / 2 + map->minY;
}

/*************************************************
 *  @brief 恢复图像偏移量和缩放比例
 *************************************************/
void QMapWidget::resetOffset()
{
    offsetX = 0;
    offsetY = 0;

    newOffsetX = 0;
    newOffsetY = 0;

    scale = 0.9f;
}

/*************************************************
 *  @brief 鼠标按钮按下事件
 *************************************************/
void QMapWidget::mousePressEvent(QMouseEvent *event)
{
    // 判断是否按下左键
    if (event->buttons() == Qt::LeftButton)
    {
        // 切换光标样式
        setCursor(cursor);

        // 初始化鼠标位置
        mouseX = event->localPos().x();
        mouseY = event->localPos().y();
    }
}

/*************************************************
 *  @brief 鼠标按钮松开事件
 *  @param event 指向 QMouseEvent 对象的指针（无用）
 *************************************************/
void QMapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    // 恢复光标样式
    unsetCursor();

    // 固化图像偏移量
    offsetX += newOffsetX;
    offsetY += newOffsetY;

    // 恢复图像偏移增量
    newOffsetX = 0;
    newOffsetY = 0;
}

/*************************************************
 *  @brief 鼠标移动事件
 *  @param event 指向 QMouseEvent 对象的指针
 *************************************************/
void QMapWidget::mouseMoveEvent(QMouseEvent *event)
{
    // 判断是否按下左键
    if (event->buttons() == Qt::LeftButton)
    {
        // 计算图像偏移量
        newOffsetX = 2 * (event->localPos().x() - mouseX) / this->width();
        newOffsetY = 2 * (mouseY - event->localPos().y()) / this->height();

        // 重绘图像
        update();
    }
}

/*************************************************
 *  @brief 鼠标滚轮事件
 *  @param event 指向 QWheelEvent 对象的指针
 *************************************************/
void QMapWidget::wheelEvent(QWheelEvent *event)
{
    scale += 0.01 * event->delta();

    // 限制缩小倍数
    if (scale < 0.9f)
    {
        scale = 0.9f;
    }

    // 重绘图像
    update();
}
