#pragma once

#include <vector>

class Instance
{
public:
	Instance(std::vector<std::vector<int>> distanceMatrix) : distanceMatrix(distanceMatrix) 
	{
		size = distanceMatrix.size();
	}

	int& operator()(int x, int y);

private:
	int size;
	std::vector<std::vector<int>> distanceMatrix;
};
