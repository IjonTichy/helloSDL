#include <iostream>
#include <fstream>
#include <SDL/SDL.h>

using namespace std;

#include "level.h"
#include "render.h"
#include "tile.h"
#include "const.h"

inline void swap(int* a, int* b)
{
    *a ^= *b; *b ^= *a; *a ^= *b;
}

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
    unsigned int x = 0, y = 0;
    ifstream ifs(filename);
    TileVector curRow;
    lightmod_t* tint;
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
            x = 0; y++;
        }
        else
        {
            tint = new lightmod_t;

            tint->r = abs((int)x-25) * 32;
            tint->g = abs((int)y-20) * 32;
            tint->b = 256;
            tint->mode = LM_MULTIPLY;

            switch (nextChar)
            {
                case '1': newTile = new Tile(this, x, y, "res/wall.png", *tint); break;
                default:  newTile = new Tile(this, x, y, "res/floor.png", *tint); break;
            }

            curRow.push_back(newTile);
            x++;
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

TileVector Level::TileLine(int x1, int y1, int x2, int y2)
{
    int endSize = max(abs(x2-x1), abs(y2-y1))+1;
    int x, y, i, index;
    bool steep, backwards;
    TileVector ret;
    ret.resize(endSize);

    steep = abs(x2-x1) < abs(y2-y1);
    if (steep)
    {
        swap(&x1, &y1);
        swap(&x2, &y2);
    }

    backwards = x1 > x2;

    if (backwards)
    {
        swap(&x1, &x2);
        swap(&y1, &y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int ystep = y1 > y2 ? -1 : 1;
    int error = dx >> 1;

    y = y1;

    for (x = x1, i = 0; x <= x2; x++, i++)
    {
        index = backwards ? (endSize - i - 1) : i;
        ret[index] = steep ? this->GetTile(y, x) : this->GetTile(x, y);

        error -= dy;

        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }

    return ret;
}
