#include "../include/Instance.h"

const int& Instance::operator()(int x, int y) const
{
    return Distance(x, y);
}

const int& Instance::Distance(int x, int y) const
{
    return distanceMatrix[x][y];
}

inline int Instance::Size() const
{
    return size;
}
