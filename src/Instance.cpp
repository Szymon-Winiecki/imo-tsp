#include "../include/Instance.h"

int& Instance::operator()(int x, int y)
{
    return distanceMatrix[x][y];
}
