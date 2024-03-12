#include <cmath>
#include <matplot/matplot.h>

#include <iostream>
#include <filesystem>

#include "../include/TSPReader.h"
#include "../include/Instance.h"

namespace fs = std::filesystem;

int main() {

    fs::path relativeDataDirPath("../../../data/");
    fs::path dataFile("kroA100.tsp");
    fs::path absoluteDataPath = fs::absolute(relativeDataDirPath / dataFile);

    TSPReader reader = TSPReader();
    Instance instance = reader.Read(absoluteDataPath);

    // get distance between two nodes like that:
    std::cout << "distance from node 7 to node 10: " << instance(7, 10) << "\n";

    return 0;
}
