#include "qgeomap.h"
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

QGeoMap::QGeoMap(QWidget *parent)
{
    this->parent = parent;
}

QGeoMap::~QGeoMap()
{
    // 指向 MainWindow 的指针置空，其内存交由系统释放
    parent = nullptr;

    // 释放线要素所占的内存
    for (QGeoPolyline *item : polyline)
    {
        delete item;
        item = nullptr;
    }
}

bool QGeoMap::loadMap(string fileName)
{
    string line, index;
    int numOfPoint, fileIndex = 0;
    float x, y;
    bool firstLine = true;

    try
    {
        // 将文件读入内存
        ifstream fs(fileName, ios::in);

        // 若文件打开失败则抛出异常
        if (!fs.is_open())
        {
            throw fileName;
        }

        // 将文件读取指针定位到线要素
        while (line != "ARC  2")
        {
            getline(fs, line);
        }

        // 读取数据
        while (true)
        {
            // 读取折线编号
            fs >> line >> index;

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
                switchFile(&fs, fileName, ++fileIndex);
            }

            // 为线要素分配内存
            QGeoPolyline *newPolyline = new QGeoPolyline(index, numOfPoint);
            polyline.push_back(newPolyline);

            // 逐点读取坐标
            for (int i = 0; i < numOfPoint; i++)
            {
                fs >> x >> y;

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

                // 判断文件流是否结束
                if (fs.eof())
                {
                    switchFile(&fs, fileName, ++fileIndex);
                }
            }
        }

        fs.close();

        return true;
    }
    catch (string fileName)
    {
        // 捕获文件读取异常，原因：找不到文件或文件格式错误
        QMessageBox::critical(parent, "Error", "Can't load file \"" + QString::fromStdString(fileName) + "\":\n\nFile missing or bad type", QMessageBox::Yes);
        return false;
    }
    catch (...)
    {
        // 捕获文件读取异常，未知原因
        QMessageBox::critical(parent, "Error", "Can't load file \"" + QString::fromStdString(fileName) + "\": Unknown error", QMessageBox::Yes);
        return false;
    }
}

void QGeoMap::switchFile(ifstream *fs, string fileName, int fileIndex)
{
    stringstream stream;
    string index, nextFileName;

    fs->close();

    stream << fileIndex + 1;
    stream >> index;
    nextFileName = fileName.substr(0, fileName.length() - (fileIndex >= 10 ? 2 : 1)) + index;

    fs->open(nextFileName, ios::in);

    // 若新文件打开失败则抛出异常
    if (!fs->is_open())
    {
        throw nextFileName;
    }
}
