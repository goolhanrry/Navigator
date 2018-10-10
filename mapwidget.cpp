#include "mapwidget.h"
#include <glu.h>
#include <iostream>
using namespace std;

MapWidget::MapWidget(QWidget *parent)
{
    this->parent = parent;
    cursor.setShape(Qt::OpenHandCursor);
}

MapWidget::~MapWidget()
{
    parent = nullptr;
}

void MapWidget::initializeGL()
{
    // 初始化 OpenGL 函数
    initializeOpenGLFunctions();

    // 全局背景色
    glClearColor(0.13f, 0.15f, 0.18f, 0);
    // 画笔颜色
    glColor3f(1, 0.8f, 0);
}

void MapWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void MapWidget::paintGL()
{
    // 边界预处理
    float dX = maxX - minX;
    float dY = maxY - minY;
    float mX = dX / 2 + minX;
    float mY = dY / 2 + minY;

    // 清空画布
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 刷新相机视角
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(offsetX + newOffsetX, offsetY + newOffsetY, 0);

    // 绘制图形
    if (this->width() * dY >= this->height() * dX)
    {
        for (auto item : polyline)
        {
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < item->size; i++)
            {
                glVertex2f(2 * scale * (item->pts[i].x - mX) * this->height() / (dY * this->width()), 2 * scale * (item->pts[i].y - mY) / dY);
            }
            glEnd();
        }
    }
    else
    {
        for (auto item : polyline)
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

void MapWidget::setPolyline(vector<QPolyline *> polyline)
{
    this->polyline = polyline;
}

void MapWidget::setBoundary(float maxX, float minX, float maxY, float minY)
{
    this->maxX = maxX;
    this->minX = minX;
    this->maxY = maxY;
    this->minY = minY;
}

void MapWidget::resetOffset()
{
    offsetX = 0;
    offsetY = 0;
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    // 判断是否按下左键
    if (event->buttons() == Qt::LeftButton)
    {
        // 切换光标样式
        setCursor(cursor);

        // 初始化鼠标位置
        mouseX = event->localPos().x();
        mouseY = event->localPos().y();

        // 初始化图像偏移量
        offsetX += newOffsetX;
        offsetY += newOffsetY;
    }
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    unsetCursor();
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    // 判断是否按下左键
    if (event->buttons() == Qt::LeftButton)
    {
        // 计算鼠标偏移量
        newOffsetX = 2 * (event->localPos().x() - mouseX) / this->width();
        newOffsetY = 2 * (mouseY - event->localPos().y()) / this->height();

        // 重绘图像
        update();
    }
}

void MapWidget::wheelEvent(QWheelEvent *event)
{

}
