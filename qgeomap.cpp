#include <QMessageBox>
#include <math.h>
#include <fstream>
#include <sstream>
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

/****************************************************
 *  @brief 从 e00 文件中读取地图数据
 *  @param fileName  待读取文件的路径
 *  @return
 *      -true   读取成功
 *      -false  读取失败
 ****************************************************/
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

/****************************************************
 *  @brief 切换待读取的文件以继续读取地图数据
 *  @param *fs       输入文件流的指针
 *  @param fileName       原文件路径
 *  @param fileIndex    当前文件索引
 ****************************************************/
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

/****************************************************
 *  @brief 使用A星算法进行路径分析
 *  @param FNode   起始结点
 *  @param TNode   目标结点
 ****************************************************/
void QGeoMap::searchPath(int FNode, int TNode)
{
    int index = 1;
    string node, path = "Path: ";
    stringstream stream;

    // 添加起始结点
    Node fNode = {FNode, 0};
    closedList.push_back(fNode);

    while (true)
    {
        // 检索相邻结点
        if (getAdjacentNode(TNode, index))
        {
            // 获取最优结点并移动一步
            getNearestNode(index);

            // 到达目标结点
            if (closedList.back() == TNode)
            {
                // 生成路径向量
                generatePath();

                // 拼接路径字符串
                for (Node item : closedList)
                {
                    stream << item.id;
                    stream >> node;
                    path += node + " -> ";
                    stream.clear();
                }

                // 触发路径更新信号
                emit pathUpdated(QString::fromStdString(path.substr(0, path.length() - 4)));

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

/****************************************************
 *  @brief 检索当前结点的相邻结点
 *  @param TNode   目标结点
 *  @param index   结点索引
 *  @return
 *      -true   获取成功
 *      -false  获取失败
 ****************************************************/
bool QGeoMap::getAdjacentNode(int TNode, int &index)
{
    float tx = nodeList.at(TNode).x;
    float ty = nodeList.at(TNode).y;
    vector<Node>::const_reverse_iterator r_iter; // 使用静态反向迭代器保证数据安全及检索效率

    for (QGeoPolyline *item : polyline)
    {
        if (closedList.back() == item->FNode)
        {
            // 若该结点已在 closedList 中则跳过
            r_iter = find(closedList.rbegin(), closedList.rend(), item->TNode);
            if (r_iter != closedList.rend())
            {
                continue;
            }

            // F (移动总耗费) = G (从起点到该点的移动量) + 2 * H (从该点到终点的预估移动量, 使用曼哈顿距离估算)
            float F = length + item->length + 2 * sqrt(pow(tx - nodeList.at(item->TNode).x, 2) + pow(ty - nodeList.at(item->TNode).y, 2));

            // 若为新结点则加入 openList
            r_iter = find(openList.rbegin(), openList.rend(), pair<int, int>(item->TNode, item->index));
            if (r_iter == openList.rend())
            {
                Node newAdjacentNode = {item->TNode, index, item->index, F};
                openList.push_back(newAdjacentNode);
            }
        }

        if (closedList.back() == item->TNode)
        {
            r_iter = find(closedList.rbegin(), closedList.rend(), item->FNode);
            if (r_iter != closedList.rend())
            {
                continue;
            }

            float F = length + item->length + 2 * sqrt(pow(tx - nodeList.at(item->FNode).x, 2) + pow(ty - nodeList.at(item->FNode).y, 2));

            r_iter = find(openList.rbegin(), openList.rend(), pair<int, int>(item->FNode, item->index));
            if (r_iter == openList.rend())
            {
                Node newAdjacentNode = {item->FNode, index, item->index, F};
                openList.push_back(newAdjacentNode);
            }
        }
    }

    // 若无可用结点则返回
    if (openList.empty())
    {
        return false;
    }

    return true;
}

/****************************************************
 *  @brief 获取最优结点并移动一步
 ****************************************************/
void QGeoMap::getNearestNode(int &index)
{
    // 获取最优结点
    Node nextNode = {0, index};
    float minF = openList.front().F;
    vector<Node>::const_iterator iter, min_iter;

    for (iter = openList.begin(); iter != openList.end(); ++iter)
    {
        if (iter->F <= minF)
        {
            minF = iter->F;
            nextNode.id = iter->id;
            min_iter = iter;
        }
    }

    // 覆盖已有路径
    if (min_iter->index < index)
    {
        while (closedList.back().index >= min_iter->index)
        {
            closedList.pop_back();
        }
    }

    // 沿最小 F 值移动
    openList.erase(min_iter);
    min_iter = openList.begin();

    closedList.push_back(nextNode);

    index++;
}

/****************************************************
 *  @brief 生成路径向量
 ****************************************************/
void QGeoMap::generatePath()
{
    vector<QGeoPolyline *> path;
    QGeoPolyline *shortestPath;

    for (int i = 0; i <= closedList.size() - 2; i++)
    {
        path.clear();

        // 检索可能路径
        for (QGeoPolyline *item : polyline)
        {
            if ((closedList.at(i) == item->FNode && closedList.at(i + 1) == item->TNode) || (closedList.at(i) == item->TNode && closedList.at(i + 1) == item->FNode))
            {
                path.push_back(item);
            }
        }

        // 计算最短路径
        shortestPath = path.front();

        for (QGeoPolyline *item : path)
        {
            if (item->length < shortestPath->length)
            {
                shortestPath = item;
            }
        }

        highlightPolyline.push_back(shortestPath);
    }
}
