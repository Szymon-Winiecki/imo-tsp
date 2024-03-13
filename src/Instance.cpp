#include "../include/Instance.h"

const int& Instance::operator()(int x, int y) const
{
    return Distance(x, y);
}

const int& Instance::Distance(int x, int y) const
{
    return distanceMatrix[x][y];
}

const int& Instance::PositionX(int node) const
{
    return positions[node][0];
}

const int& Instance::PositionY(int node) const
{
    return positions[node][1];
}

int Instance::Size() const
{
    return size;
}
