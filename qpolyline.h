#ifndef QPOLYLINE_H
#define QPOLYLINE_H

#include <QPoint>

class QPolyline
{
  public:
    QPolyline();

    void addPoint(int x, int y);
    void setSize(int size);

    int size, count = 0;
    QPoint *pts;
};

#endif // QPOLYLINE_H
