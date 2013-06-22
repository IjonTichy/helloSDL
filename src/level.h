#ifndef _HELLOSDL_LEVEL__
#define _HELLOSDL_LEVEL__

#include <vector>

#define LEVEL_H 16
#define LEVEL_W 16

struct levelsize { int w; int h; };
typedef std::vector< std::vector<int> > MapVector;

class Level
{
    private:
        unsigned int width, height;
        MapVector map;

    public:
        int getTile(int x, int y);
        int fromFile(char * filename);
        struct levelsize size(void);
};

#endif
