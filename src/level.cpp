#include <iostream>
#include <fstream>

using namespace std;

#include "level.h"
#include "render.h"

int tmpLevel[LEVEL_H][LEVEL_W] = 
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,1,1,1,1,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,1,1,1,1,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int Level::getTile(int x, int y)
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
    {
        return -1;
    }

    return this->map[y][x];
}

int Level::fromFile(char * filename)
{
    char nextChar;
    unsigned int maxLength = 0;
    ifstream ifs(filename);
    vector<int> curRow;

    if (ifs.fail()) { return 1; }

    this->map.clear();

    curRow.clear();

    while (1)
    {
        nextChar = (char)ifs.get();
        if (nextChar == -1) { break; }

        if (nextChar == '\r' || nextChar == '\n')
        {
            maxLength = max(maxLength, (unsigned int)curRow.size());
            this->map.push_back(curRow);
            curRow.clear();
            printf("\n");
        }
        else
        {
            switch (nextChar)
            {
                case '1': curRow.push_back(1); break;
                default:  curRow.push_back(0); break;
            }
            printf("%c", nextChar);
        }
    }

    MapVector::iterator mapIter;

    for (mapIter = this->map.begin(); mapIter != this->map.end(); ++mapIter)
    {
        mapIter->resize(maxLength);
    }

    this->width = maxLength;
    this->height = (unsigned int)this->map.size();

    printf("Row length comes out to %u\n", maxLength);

    return 0;
} 

struct levelsize Level::size(void)
{
    struct levelsize ret = {this->width, this->height};
    return ret;
}
