#include <cmath>
#include <iostream>
#include <filesystem>
#include <format>
#include <vector>
#include <string>

#include "../include/TSPReader.h"
#include "../include/Instance.h"
#include "../include/NearestNeighborSolver.h"
#include "../include/GreedyCycleSolver.h"
#include "../include/RegretSolver.h"
#include "../include/Result.h"
#include "../include/Experiment.h"

namespace fs = std::filesystem;

int main() {

    fs::path relativeProjectRootDir("../../../");
    const int experiments = 100;
    const int algorithms = 1;

    // read file with the input data
    fs::path absoluteDataPath = fs::absolute(relativeProjectRootDir / "data" / "kroB100.tsp");
    TSPReader reader = TSPReader();
    Instance instance = reader.Read(absoluteDataPath);
    Experiment experiment = Experiment(algorithms);

    // create results directory, if not exists
    if (!fs::is_directory(relativeProjectRootDir / "results") || !fs::exists(relativeProjectRootDir / "results")) {
        fs::create_directory(relativeProjectRootDir / "results");
    }

    // run solver
    NearestNeighborSolver solver1 = NearestNeighborSolver(&instance);
    RegretSolver solver2 = RegretSolver(&instance);
    GreedyCycleSolver solver3 = GreedyCycleSolver(&instance);

    int length = 0;
    
    //for (int j = 0; j < algorithms; j++)
    //{
    int j = 0;
    for (int i = 0; i < experiments; i++)
    {
        std::string json_output = std::to_string(i) + "_" + std::to_string(j);
        json_output += "export2.json";
        fs::path exportPath = fs::absolute(relativeProjectRootDir / "results" / json_output);
        if (j == 0)
        {
            Result* result = solver1.Solve(2);
            length = result->getRouteLength();
            result->ExportAsJSON(exportPath);
        }
        else if (j == 1)
        {
            Result* result = solver2.Solve(2);
            length = result->getRouteLength();
            result->ExportAsJSON(exportPath);
        }
        else if (j == 2)
        {
            Result* result = solver3.Solve(2);
            length = result->getRouteLength();
            result->ExportAsJSON(exportPath);
        }

        experiment.add_result(j, length);


    }
    //}


    fs::path ResultExportPath = fs::absolute(relativeProjectRootDir / "results" / "results.txt");

    //experiment.show_results();
    experiment.save_results(ResultExportPath);

    /*
    // run python script to draw the graph (the result is both saved in results/plot.png file and displayed on the screen)
    fs::path plotPath = fs::absolute(relativeProjectRootDir / "results" / "plot.png");
    fs::path visualizerScriptPath = fs::absolute(relativeProjectRootDir / "visualization" / "visualize.py");
    system(std::format("python {} {} {}", visualizerScriptPath.string(), exportPath.string(), plotPath.string()).c_str());
    */
    return 0;
}
