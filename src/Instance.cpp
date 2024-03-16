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

const std::array<int, 2>& Instance::Position(int node) const
{
    return positions[node];
}

float Instance::PositionX_Normalized(int node) const
{
    return (positions[node][0] - xNormalizationOffset) * xNormalizationRatio;
}

float Instance::PositionY_Normalized(int node) const
{
    return (positions[node][1] - yNormalizationOffset) * yNormalizationRatio;
}

std::array<float, 2> Instance::Position_Normalized(int node) const
{
    return { PositionX_Normalized(node), PositionY_Normalized(node) };
}

int Instance::Size() const
{
    return size;
}
