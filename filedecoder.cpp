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
    int offset, numOfPoint, index = 0;
    float x, y;
    bool firstLine = true;

    try
    {
        // 将文件读入内存
        ifstream fs(fileName, ios::in);

        // 获取数据长度
        fs.seekg(-57, ios::end);
        getline(fs, buffer);
        offset = buffer.length() ? -85 : -56;

        while (true)
        {
            fs.seekg(offset, ios::end);
            getline(fs, buffer);

            if (buffer[10] != 'E')
            {
                offset -= 12;
                break;
            }

            offset -= 57;
        }

        fs.seekg(offset, ios::end);
        getline(fs, buffer);

        stream << buffer.substr(0, 9);
        stream >> size;
        stream.clear();

        // 初始化 QPolyline 数组
        polyline = new QPolyline[size];

        // 将文件读取指针定位到线要素
        fs.seekg(0, ios::beg);
        while (buffer != "ARC  2")
        {
            getline(fs, buffer);
        }

        // 读取数据
        while (getline(fs, buffer))
        {
            // 读取一条折线所包含点的个数
            stream << buffer.substr(66, 4);
            stream >> numOfPoint;
            stream.clear();

            // 初始化 QPolyline 大小
            polyline[index].setSize(numOfPoint);

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

                polyline[index].addPoint(x, y);

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

                polyline[index].addPoint(x, y);
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

                polyline[index].addPoint(x, y);
            }

            index++;
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
