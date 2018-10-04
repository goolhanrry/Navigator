#include "filedecoder.h"
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

FileDecoder::FileDecoder(string fileName)
{
    this->fileName = fileName;
}

bool FileDecoder::decodeFile()
{
    string buffer;
    stringstream stream;
    int size;
    float x, y;

    try
    {
        // 将文件读入内存
        ifstream fs(fileName, ios::in);

        // 将文件读取指针定位到线要素
        while (buffer != "ARC  2")
        {
            getline(fs, buffer);
        }

        // 读取数据
        while (getline(fs, buffer))
        {
            // 读取一条折线所包含点的个数
            stream << buffer.substr(66, 69);
            stream >> size;
            stream.clear();

            QPolyline *newPolyline = new QPolyline(size);
            polyline->push_back(newPolyline);

            // 逐行读取坐标
            for (int i = 0; i < size / 2; i++)
            {
                getline(fs, buffer);

                stream << buffer.substr(1, 13);
                stream >> x;
                stream.clear();

                stream << buffer.substr(15, 27);
                stream >> y;
                stream.clear();

                polyline->back()->addPoint(int(x * COEFFICIENT), int(y * COEFFICIENT));
                stream << buffer.substr(29, 41);
                stream >> x;
                stream.clear();

                stream << buffer.substr(43, 55);
                stream >> y;
                stream.clear();

                polyline->back()->addPoint(int(x * COEFFICIENT), int(y * COEFFICIENT));
            }
            if (!size % 2)
            {
                getline(fs, buffer);

                stream << buffer.substr(1, 13);
                stream >> x;
                stream.clear();

                stream << buffer.substr(15, 27);
                stream >> y;
                stream.clear();

                polyline->back()->addPoint(int(x * COEFFICIENT), int(y * COEFFICIENT));
            }
        }

        fs.close();

        return true;
    }
    catch (exception e)
    {
        // 文件读取失败，返回 false
        return false;
    }
}
