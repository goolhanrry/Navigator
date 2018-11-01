#include "qgeomap.h"
#include <QMessageBox>
#include <fstream>
#include <sstream>
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

/*************************************************
 *  @brief 从 e00 文件中读取地图数据
 *  @param fileName   待读取的文件路径
 *  @return
 *      -true   读取成功
 *      -false  读取失败
 *************************************************/
bool QGeoMap::loadMap(string fileName)
{
    string buffer;
    int index, FNode, TNode, LPoly, RPoly, numOfPoint, fileIndex = 0;
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
        while (buffer != "ARC  2" & buffer != "ARC  3")
        {
            getline(fs, buffer);
        }

        // 读取数据
        while (true)
        {
            // 读取折线数据
            fs >> buffer >> index >> FNode >> TNode >> LPoly >> RPoly >> numOfPoint;

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
            QGeoPolyline *newPolyline = new QGeoPolyline(index, FNode, TNode, numOfPoint);
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
        // 捕获文件读取异常，原因：找不到文件或文件编码错误
        QMessageBox::critical(parent, "Error", "Can't load file \"" + QString::fromStdString(fileName) + "\":\n\nFile Missing or Bad Encoding", QMessageBox::Yes);
        return false;
    }
    catch (...)
    {
        // 捕获文件读取异常，原因：文件格式错误
        QMessageBox::critical(parent, "Error", "Can't load file \"" + QString::fromStdString(fileName) + "\":\n\nBad Format", QMessageBox::Yes);
        return false;
    }
}

/*************************************************
 *  @brief 切换待读取的文件以继续读取地图数据
 *  @param *fs       输入文件流的指针
 *  @param fileName       原文件路径
 *  @param fileIndex    当前文件索引
 *************************************************/
void QGeoMap::switchFile(ifstream *fs, string fileName, int fileIndex)
{
    stringstream stream;
    string index, nextFileName;

    fs->close();

    stream << fileIndex;
    stream >> index;
    nextFileName = fileName.substr(0, fileName.length() - (fileIndex >= 10 ? 2 : 1)) + index;

    fs->open(nextFileName, ios::in);

    // 若新文件打开失败则抛出异常
    if (!fs->is_open())
    {
        throw nextFileName;
    }
}
