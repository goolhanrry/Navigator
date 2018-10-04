#include "mapwidget.h"

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
    glColor3f(0.9f, 0.9f, 0.9f);
}

void MapWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void MapWidget::paintGL()
{
    // 清空画布
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
