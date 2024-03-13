#include <cmath>
#include <iostream>
#include <filesystem>

#include "../include/TSPReader.h"
#include "../include/Instance.h"
#include "../include/NearestNeighborSolver.h"
#include "../include/Result.h"

namespace fs = std::filesystem;

int main() {

    fs::path relativeDataDirPath("../../../data/");
    fs::path dataFile("kroA100.tsp");
    fs::path absoluteDataPath = fs::absolute(relativeDataDirPath / dataFile);

    TSPReader reader = TSPReader();
    Instance instance = reader.Read(absoluteDataPath);

    // get distance between two nodes like that:
    std::cout << "distance from node 7 to node 10: " << instance.Distance(7, 10) << "\n";

    // or like that:
    std::cout << "distance from node 7 to node 10: " << instance(7, 10) << "\n";

    NearestNeighborSolver solver = NearestNeighborSolver(&instance);
    Result* result = solver.Solve();

    result->Plot();

    return 0;
}
