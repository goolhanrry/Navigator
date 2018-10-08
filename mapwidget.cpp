#include "mapwidget.h"
#include <iostream>
using namespace std;

MapWidget::MapWidget(QWidget *parent)
{
    this->parent = parent;
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
    this->fixScale(width, height);
}

void MapWidget::paintGL()
{
    // 边界预处理
    float mX = (maxX - minX) / 2;
    float mY = (maxY - minY) / 2;
    float dX = mX + minX;
    float dY = mY + minY;

    // 绘图比例修正
    this->fixScale(this->width(), this->height());

    // 清空画布
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glBegin(GL_LINE_LOOP);
    // glVertex2f(0.9f, 0.9f);
    // glVertex2f(0.9f, -0.9f);
    // glVertex2f(-0.9f, -0.9f);
    // glVertex2f(-0.9f, 0.9f);
    // glEnd();

    // 绘制图形
    for (int i = 0; i < size; i++)
    {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < polyline[i].size; j++)
        {
            glVertex2f((polyline[i].pts[j].x - dX) / mX, (polyline[i].pts[j].y - dY) / mY);
        }
        glEnd();
    }
}

void MapWidget::setPolyline(QPolyline *polyline, int size)
{
    this->polyline = polyline;
    this->size = size;
}

void MapWidget::setBoundary(float maxX, float minX, float maxY, float minY)
{
    this->maxX = maxX;
    this->minX = minX;
    this->maxY = maxY;
    this->minY = minY;
}

void MapWidget::fixScale(int width, int height)
{
    float dX = maxX - minX;
    float dY = maxY - minY;

    if (dX >= dY)
    {
        glViewport(0.1f * width, height - 0.9f * width * dY / dX, 1.8f * width, 1.8f * width * dY / dX);
    }
    else
    {
        glViewport(width - 0.9f * height * dX / dY, 0.1f * height, 1.8f * height * dX / dY, 1.8f * height);
    }
}
