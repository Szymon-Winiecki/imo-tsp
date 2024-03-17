#include <cmath>
#include <iostream>
#include <filesystem>
#include <format>

#include "../include/TSPReader.h"
#include "../include/Instance.h"
#include "../include/NearestNeighborSolver.h"
#include "../include/GreedyCycleSolver.h"
#include "../include/Result.h"

namespace fs = std::filesystem;

int main() {

    fs::path relativeProjectRootDir("../../../");

    // read file with the input data
    fs::path absoluteDataPath = fs::absolute(relativeProjectRootDir / "data" / "kroA100.tsp");
    TSPReader reader = TSPReader();
    Instance instance = reader.Read(absoluteDataPath);


    // run solver
    //NearestNeighborSolver solver = NearestNeighborSolver(&instance);
    GreedyCycleSolver solver = GreedyCycleSolver(&instance);
    Result* result = solver.Solve(2);


    // create results directory, if not exists
    if (!fs::is_directory(relativeProjectRootDir / "results") || !fs::exists(relativeProjectRootDir / "results")) {
        fs::create_directory(relativeProjectRootDir / "results");
    }

    // save result as a JSON file
    fs::path exportPath = fs::absolute(relativeProjectRootDir / "results" / "export.json");
    result->ExportAsJSON(exportPath);

    // run python script to draw the graph (the result is both saved in results/plot.png file and displayed on the screen)
    fs::path plotPath = fs::absolute(relativeProjectRootDir / "results" / "plot.png");
    fs::path visualizerScriptPath = fs::absolute(relativeProjectRootDir / "visualization" / "visualize.py");
    system(std::format("python {} {} {}", visualizerScriptPath.string(), exportPath.string(), plotPath.string()).c_str());

    return 0;
}
