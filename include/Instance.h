#pragma once

#include <vector>
#include <array>

class Instance
{
public:
	Instance(std::vector<std::vector<int>> distanceMatrix) : Instance(distanceMatrix, {}) {}

	Instance(std::vector<std::vector<int>> distanceMatrix, std::vector<std::array<int, 2>> positions) : distanceMatrix{ distanceMatrix }, positions{ positions }
	{
		size = distanceMatrix.size();
	}

	const int& operator()(int x, int y) const;
	inline const int& Distance(int x, int y) const;
	inline int Size() const;

private:
	int size;
	std::vector<std::vector<int>> distanceMatrix;
	std::vector<std::array<int, 2>> positions; //optional, only for visualisation
};
