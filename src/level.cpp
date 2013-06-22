#include <iostream>
#include <fstream>

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
    if (x < 0 || x >= LEVEL_W || y < 0 || y >= LEVEL_H)
    {
        return -1;
    }

    return tmpLevel[y][x];
}

int Level::fromFile(char * filename)
{
    int curLength, maxLength;
    int height;

    char nextChar;
    std::ifstream ifs(filename);

    if (ifs.fail()) { return 1; }

    while (1)
    {
        nextChar = (char)ifs.get();
        if (nextChar == -1) { break; }
    }

    return 0;
} 
