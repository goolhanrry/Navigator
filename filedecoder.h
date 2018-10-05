#ifndef FILEDECODER_H
#define FILEDECODER_H

#define COEFFICIENT 100000

#include <string>
#include "mainwindow.h"
#include "qpolyline.h"
using namespace std;

class FileDecoder
{
public:
  FileDecoder(string fileName);

  bool decodeFile(); // 文件解析方法

  QPolyline *polyline;
  int size;
  float maxX, minX, maxY, minY;

private:
  string fileName;
};

#endif // FILEDECODER_H
