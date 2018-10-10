#ifndef FILEDECODER_H
#define FILEDECODER_H

#include <string>
#include <vector>
#include "mainwindow.h"
#include "qpolyline.h"
using namespace std;

class FileDecoder
{
public:
  FileDecoder(string fileName);

  bool decodeFile(); // 文件解析方法

  vector<QPolyline *> polyline;
  float maxX, minX, maxY, minY;

protected:
  void switchFile(ifstream *fs, int fileIndex);

  string fileName;
};

#endif // FILEDECODER_H
