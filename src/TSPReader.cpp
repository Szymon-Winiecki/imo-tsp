#include "../include/TSPReader.h"
#include "../include/Instance.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <cmath>

Instance TSPReader::Read(const std::filesystem::path& filepath)
{
    auto nodesPositions = ReadNodesPositions(filepath);
    auto distanceMatrix = NodesPositionsToDistanceMatrix(nodesPositions);
	return Instance(distanceMatrix);
}

std::vector<std::vector<int>> TSPReader::ReadNodesPositions(const std::filesystem::path& filepath)
{
    std::string line;
    std::ifstream file(filepath);

    std::vector<std::vector<int>> positions{};

    bool isInNodeCoordSection = false;
    int instanceSize = 0;       // number of nodes in the instance
    int i = 0, x = 0, y = 0;    // variables to read node's index, x pos and y pos

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (!isInNodeCoordSection && line.starts_with("DIMENSION")) {
                instanceSize = std::stoi(line.substr(11));  // 11 is the number of characters in the phrase 'DIMENSION: '
                positions.resize(instanceSize);
            }
            if (!isInNodeCoordSection && line.starts_with("NODE_COORD_SECTION")) {
                isInNodeCoordSection = true;
                continue;
            }
            if (isInNodeCoordSection) {
                std::stringstream ss(line);
                ss >> i >> x >> y;

                positions[i - 1] = { x, y };

                if (i == instanceSize) break;
            }

        }
        file.close();
    }

    return positions;
}

std::vector<std::vector<int>> TSPReader::NodesPositionsToDistanceMatrix(const std::vector<std::vector<int>>& nodesPositions)
{
    int size = nodesPositions.size();
    std::vector<std::vector<int>> distances(size);
    for (int i = 0; i < size; ++i) {
        distances[i].resize(size);

        for (int j = 0; j < i; ++j) {

            int xdif = nodesPositions[i][0] - nodesPositions[j][0];
            int ydif = nodesPositions[i][1] - nodesPositions[j][1];
            float distance = sqrt(xdif * xdif + ydif * ydif);

            distances[i][j] = round(distance);
        }

        distances[i][i] = 0;
    }

    for (int i = 0; i < size; ++i) {

        for (int j = i + 1; j < size; ++j) {

            distances[i][j] = distances[j][i];
        }
    }

	return distances;
}