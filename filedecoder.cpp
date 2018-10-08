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
    string line, index;
    int numOfPoint, fileIndex = 0;
    float x, y;
    bool firstLine = true;

    try
    {
        // 将文件读入内存
        ifstream fs(fileName, ios::in);

        // 将文件读取指针定位到线要素
        while (line != "ARC  2")
        {
            getline(fs, line);
        }

        fs.seekg(10, ios::cur);

        // 读取数据
        while (!fs.eof())
        {
            // 读取折线编号
            fs >> index;

            // 读取一条折线所包含点的个数
            fs.seekg(45, ios::cur);
            fs >> numOfPoint;

            // 判断线要素是否结束
            if (!numOfPoint)
            {
                break;
            }

            // 判断文件流是否结束
            if (fs.eof())
            {
                switchFile(&fs, ++fileIndex);
                break;
            }

            // 为线要素分配内存
            QPolyline *newPolyline = new QPolyline(index, numOfPoint);
            polyline.push_back(newPolyline);

            // 逐行读取坐标
            for (int i = 0; i < numOfPoint; i++)
            {
                fs >> x >> y;

                // 判断文件流是否结束
                if (fs.eof())
                {
                    switchFile(&fs, ++fileIndex);
                    continue;
                }

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
            }

            // 读取到文件末尾时将 eofbit 置为 true
            fs >> line;
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

void FileDecoder::switchFile(ifstream *fs, int fileIndex)
{
    stringstream stream;
    string index;

    fs->close();

    stream << fileIndex;
    stream >> index;
    fileName = fileName.substr(0, fileName.length() - (fileIndex >= 10 ? 2 : 1)) + index;

    fs->open(fileName, ios::in);
}
