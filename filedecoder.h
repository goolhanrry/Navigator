#ifndef FILEDECODER_H
#define FILEDECODER_H

#include <string>
using namespace std;

class FileDecoder
{
  public:
    FileDecoder(string fileName);
    ~FileDecoder();
    void decodeFile(); // 文件解析方法

  private:
    string fileName;
};

#endif // FILEDECODER_H
