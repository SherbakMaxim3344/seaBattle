#ifndef INFO_HOLDER_H
#define INFO_HOLDER_H

#include "inputHandler.h"

class InfoHolder
{
public:
    virtual void RequestData() = 0;
    virtual ~InfoHolder() = default;
};

class CoordHolder : public InfoHolder
{
private:
    CoordReader coord_reader;
    std::pair<int, int> coords;

public:
    void RequestData();

    std::pair<int, int> GetCoords();
};

#endif 
