#pragma once

#include <vector>
#include <string>
#include <filesystem>

class Instance;

class TSPReader
{
public:
	Instance Read(const std::filesystem::path& filepath);

private:
	std::vector<std::vector<int>> ReadNodesPositions(const std::filesystem::path& filepath);
	std::vector<std::vector<int>> NodesPositionsToDistanceMatrix(const std::vector<std::vector<int>>& nodesPositions);

};