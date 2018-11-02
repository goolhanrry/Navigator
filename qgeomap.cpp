#include <QMessageBox>
#include <math.h>
#include <iostream>
#include "qgeomap.h"

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
 *  @param fileName  待读取文件的路径
 *  @return
 *      -true   读取成功
 *      -false  读取失败
 *************************************************/
bool QGeoMap::loadMap(string fileName)
{
    string buffer;
    int index, FNode, TNode, LPoly, RPoly, size, fileIndex = 0;
    float x, y;
    bool firstPoint = true;

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
        while (buffer != "ARC  2" && buffer != "ARC  3")
        {
            getline(fs, buffer);
        }

        // 读取数据
        while (true)
        {
            // 读取折线数据
            fs >> buffer >> index >> FNode >> TNode >> LPoly >> RPoly >> size;

            // 判断线要素是否结束
            if (!size)
            {
                break;
            }

            // 判断文件流是否结束
            if (fs.eof())
            {
                switchFile(&fs, fileName, ++fileIndex);
            }

            // 为线要素分配内存
            QGeoPolyline *newPolyline = new QGeoPolyline(index, FNode, TNode, size);
            polyline.push_back(newPolyline);

            // 逐点读取坐标
            for (int i = 0; i < size; i++)
            {
                fs >> x >> y;

                // 初始化边界
                maxX = (firstPoint || x > maxX) ? x : maxX;
                minX = (firstPoint || x < minX) ? x : minX;
                maxY = (firstPoint || y > maxY) ? y : maxY;
                minY = (firstPoint || y < minY) ? y : minY;

                firstPoint = false;

                // 添加结点
                if (!i)
                {
                    nodeList[FNode] = QGeoPoint(x, y);
                }

                newPolyline->addPoint(x, y);

                // 判断文件流是否结束
                if (fs.eof())
                {
                    switchFile(&fs, fileName, ++fileIndex);
                }
            }

            // 添加结点
            nodeList[TNode] = QGeoPoint(x, y);
        }

        fs.close();

        return true;
    }
    catch (string fileName)
    {
        // 捕获文件读取异常，原因：找不到文件或文件编码错误
        QMessageBox::critical(parent, "Error", "Can't load file \"" + QString::fromStdString(fileName) + "\":\n\nFile Missing or Bad Encoding", QMessageBox::Ok);
        return false;
    }
    catch (...)
    {
        // 捕获文件读取异常，原因：文件格式错误
        QMessageBox::critical(parent, "Error", "Can't load file \"" + QString::fromStdString(fileName) + "\":\n\nBad Format", QMessageBox::Ok);
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

/*************************************************
 *  @brief 使用A星算法进行路径分析
 *  @param FNode   起始结点
 *  @param TNode   目标结点
 *************************************************/
void QGeoMap::searchPath(int FNode, int TNode)
{
    // 添加起始结点
    int index, currentNode = FNode;
    closedList.push_back(currentNode);

    while (true)
    {
        // 检索相邻结点
        if (getAdjacentNode(currentNode, TNode, index))
        {
            cout << currentNode << endl;

            // 沿最小 F 值移动
            closedList.push_back(currentNode);

            // 到达目标结点
            if (currentNode == TNode)
            {
                break;
            }
        }
        else
        {
            QMessageBox::information(parent, "Notice", "Path not found", QMessageBox::Ok);
            break;
        }
    }
}

/*************************************************
 *  @brief 检索相邻结点并返回最优邻接结点
 *  @param currentNode  当前结点
 *  @param TNode        目标结点
 *  @return
 *      -true   获取成功
 *      -false  获取失败
 *************************************************/
bool QGeoMap::getAdjacentNode(int &currentNode, int TNode, int &index)
{
    float tx = nodeList.at(TNode).x;
    float ty = nodeList.at(TNode).y;
    vector<int>::iterator iter;
    vector<Node>::reverse_iterator r_iter;

    for (QGeoPolyline *item : polyline)
    {
        if (item->FNode == currentNode)
        {
            // F (移动总耗费) = G (从起点到该点的移动量) + H (从该点到终点的预估移动量, 使用曼哈顿距离估算)
            float F = length + item->length + sqrt(pow(tx - nodeList.at(item->TNode).x, 2) + pow(ty - nodeList.at(item->TNode).y, 2));

            // 若该结点已在 closedList 中则跳过
            iter = find(closedList.begin(), closedList.end(), item->TNode);
            if (iter != closedList.end())
            {
                continue;
            }

            // 若为新结点则加入 openList
            r_iter = find(openList.rbegin(), openList.rend(), item->TNode);
            if (r_iter == openList.rend())
            {
                Node newAdjacentNode = {item->TNode, index, F};
                openList.push_back(newAdjacentNode);
            }
        }
        else if (item->TNode == currentNode)
        {
            float F = length + item->length + sqrt(pow(tx - nodeList.at(item->FNode).x, 2) + pow(ty - nodeList.at(item->FNode).y, 2));

            iter = find(closedList.begin(), closedList.end(), item->FNode);
            if (iter != closedList.end())
            {
                continue;
            }

            r_iter = find(openList.rbegin(), openList.rend(), item->FNode);
            if (r_iter == openList.rend())
            {
                Node newAdjacentNode = {item->FNode, index, F};
                openList.push_back(newAdjacentNode);
            }
        }
    }

    // 若无可用结点则返回
    if (openList.empty())
    {
        return false;
    }

    // 从 openList 中取出最优结点
    vector<Node>::iterator node_iter, min_iter;
    float minF = openList.front().F;

    for (node_iter = openList.begin(); node_iter != openList.end(); ++node_iter)
    {
        if (node_iter->F <= minF)
        {
            minF = node_iter->F;
            currentNode = node_iter->id;
            min_iter = node_iter;
        }
    }

    openList.erase(min_iter);
    min_iter = openList.begin();

    return true;
}
