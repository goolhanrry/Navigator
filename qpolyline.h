#ifndef QPOLYLINE_H
#define QPOLYLINE_H

#include <QPoint>

class QPolyline
{
  public:
    QPolyline(int size);

    void addPoint(int x, int y);

    int size, count = 0;
    QPoint *pts;
};

#endif // QPOLYLINE_H
