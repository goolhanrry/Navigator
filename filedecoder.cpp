#include "filedecoder.h"
#include <iostream>
#include <fstream>
using namespace std;

FileDecoder::FileDecoder(string fileName)
{
    this->fileName = fileName;
    decodeFile();
}

FileDecoder::~FileDecoder()
{
}

void FileDecoder::decodeFile()
{
    ifstream fs(fileName, ios::in);

    string temp;
    while (getline(fs, temp))
    {
        cout << temp << endl;
    }

    fs.close();
}
