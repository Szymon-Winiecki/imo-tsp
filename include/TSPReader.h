#pragma once

#include <vector>
#include <array>
#include <string>
#include <filesystem>

class Instance;

class TSPReader
{
public:
	Instance Read(const std::filesystem::path& filepath, bool bSavePositions = true);

private:
	std::vector<std::array<int, 2>> ReadNodesPositions(const std::filesystem::path& filepath);
	std::vector<std::vector<int>> NodesPositionsToDistanceMatrix(const std::vector<std::array<int, 2>>& nodesPositions);

};