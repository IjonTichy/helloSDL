#ifndef _HELLOSDL_LEVEL__
#define _HELLOSDL_LEVEL__

#include <vector>

#define LEVEL_H 16
#define LEVEL_W 16

struct levelsize { int w; int h; };

class Level
{
    private:
        int x, y;
        std::vector< std::vector<int> > map;

    public:
        int getTile(int x, int y);
        int fromFile(char * filename);
        int size(void);
};

#endif
