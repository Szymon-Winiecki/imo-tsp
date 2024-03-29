#pragma once

#include <vector>
#include <array>

// a class representing a data instance (distances between vertices)
class Instance
{
public:
	Instance(std::vector<std::vector<int>> distanceMatrix) : Instance(distanceMatrix, {}) {}

	Instance(std::vector<std::vector<int>> distanceMatrix, std::vector<std::array<int, 2>> positions) : distanceMatrix{ distanceMatrix }, positions{ positions }
	{
		size = distanceMatrix.size();


		if (positions.empty()) return;

		// nodes positions normalization (only for visualization)

		int minX{ positions[0][0] };
		int	maxX{ positions[0][0] };
		int minY{ positions[0][1] };
		int	maxY{ positions[0][1] };

		for (auto position : positions)
		{
			if (position[0] < minX)
			{
				minX = position[0];
			}
			else if (position[0] > maxX)
			{
				maxX = position[0];
			}

			if (position[1] < minY)
			{
				minY = position[1];
			}
			else if (position[1] > maxY)
			{
				maxY = position[1];
			}
		}

		xNormalizationOffset = minX;
		xNormalizationRatio = 1.f / (maxX - minX);
		yNormalizationOffset = minY;
		yNormalizationRatio = 1.f / (maxY - minY);
	}

	// get distance between nodes x and y
	const int& operator()(int x, int y) const;
	const int& Distance(int x, int y) const;

	// get position of the node
	const int& PositionX(int node) const;
	const int& PositionY(int node) const;
	const std::array<int, 2>& Position(int node) const;

	// get normalized position of the node (x and y coords in range <0,1>)
	float PositionX_Normalized(int node) const;
	float PositionY_Normalized(int node) const;
	std::array<float, 2> Position_Normalized(int node) const;

	// get instance size (number of nodes)
	int Size() const;

private:
	int size;
	int xNormalizationOffset{ 0 }, yNormalizationOffset{ 0 };
	float xNormalizationRatio{ 1 }, yNormalizationRatio{ 1 };
	std::vector<std::vector<int>> distanceMatrix;
	std::vector<std::array<int, 2>> positions; //optional, only for visualisation
};
