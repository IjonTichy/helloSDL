#include <iostream>
#include <fstream>
#include <SDL/SDL.h>

using namespace std;

#include "level.h"
#include "render.h"
#include "tile.h"
#include "const.h"

Level::Level(void)
{
    this->map.clear();
    this->width = 0;
    this->height = 0;
}

Tile* Level::GetTile(int x, int y)
{
    unsigned int x2 = (unsigned int)x;
    unsigned int y2 = (unsigned int)y;

    if (x2 < 0 || x2 >= this->width || y2 < 0 || y2 >= this->height)
    {
        return NULL;
    }

    return this->map[y][x];
}

int Level::FromFile(char * filename)
{
    char nextChar;
    unsigned int maxLength = 0;
    ifstream ifs(filename);
    vector<Tile*> curRow;
    Tile* newTile;

    if (ifs.fail()) { return 1; }

    this->map.clear();

    curRow.clear();

    printf("Loading level...\n");

    while (1)
    {
        nextChar = (char)ifs.get();
        if (nextChar == -1) { break; }

        if (nextChar == '\r' || nextChar == '\n')
        {
            maxLength = max(maxLength, (unsigned int)curRow.size());
            this->map.push_back(curRow);
            curRow.clear();
        }
        else
        {
            switch (nextChar)
            {
                case '1': newTile = new Tile(this, "res/wall.png"); break;
                default:  newTile = new Tile(this, "res/floor.png"); break;
            }

            curRow.push_back(newTile);
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

struct levelsize Level::Size(void)
{
    struct levelsize ret = {this->width, this->height};
    return ret;
}

void Level::Render(SDL_Surface* screen, int baseX, int baseY)
{
    int i, j, x, y;
    int xmin, xmax, ymin, ymax;
    Tile* tile;

    xmin = -(baseX / TILE_WIDTH);
    ymin = -(baseY / TILE_HEIGHT);

    xmax = (-baseX + (int)screen->w + TILE_WIDTH - 1) / TILE_WIDTH;
    ymax = (-baseY + (int)screen->h + TILE_HEIGHT - 1) / TILE_HEIGHT;

    xmax = (int)min(this->width, (unsigned int)xmax);
    ymax = (int)min(this->height, (unsigned int)ymax);

    for (i = xmin; i < xmax; i++)
    {
        for (j = ymin; j < ymax; j++)
        {
            x = baseX + (TILE_WIDTH  * i);
            y = baseY + (TILE_HEIGHT * j);

            tile = this->GetTile(i, j);

            if (tile == NULL) { continue; }

            tile->Render(x, y, screen);
        }
    }
}
