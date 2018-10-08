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
    string buffer, index;
    stringstream stream;
    int numOfPoint;
    float x, y;
    bool firstLine = true;

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
            // 读取折线编号
            index = buffer.substr(0, 10);
            index.erase(0, index.find_first_not_of(" "));

            // 读取一条折线所包含点的个数
            stream << buffer.substr(66, 4);
            stream >> numOfPoint;
            stream.clear();

            // 判断线要素是否结束
            if (!numOfPoint)
            {
                break;
            }

            // 为线要素分配内存
            QPolyline *newPolyline = new QPolyline(index, numOfPoint);
            polyline.push_back(newPolyline);

            // 逐行读取坐标
            for (int i = 0; i < numOfPoint / 2; i++)
            {
                getline(fs, buffer);

                stream << buffer.substr(1, 13);
                stream >> x;
                stream.clear();

                stream << buffer.substr(15, 13);
                stream >> y;
                stream.clear();

                // 初始化边界
                if (firstLine)
                {
                    firstLine = false;
                    maxX = x;
                    minX = x;
                    maxY = y;
                    minY = y;
                }
                else
                {
                    maxX = x > maxX ? x : maxX;
                    minX = x < minX ? x : minX;
                    maxY = y > maxY ? y : maxY;
                    minY = y < minY ? y : minY;
                }

                polyline.back()->addPoint(x, y);

                stream << buffer.substr(29, 13);
                stream >> x;
                stream.clear();

                stream << buffer.substr(43, 13);
                stream >> y;
                stream.clear();

                maxX = x > maxX ? x : maxX;
                minX = x < minX ? x : minX;
                maxY = y > maxY ? y : maxY;
                minY = y < minY ? y : minY;

                polyline.back()->addPoint(x, y);
            }

            if (numOfPoint % 2)
            {
                getline(fs, buffer);

                stream << buffer.substr(1, 13);
                stream >> x;
                stream.clear();

                stream << buffer.substr(15, 13);
                stream >> y;
                stream.clear();

                maxX = x > maxX ? x : maxX;
                minX = x < minX ? x : minX;
                maxY = y > maxY ? y : maxY;
                minY = y < minY ? y : minY;

                polyline.back()->addPoint(x, y);
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
