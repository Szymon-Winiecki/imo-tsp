#include <cmath>
#include <iostream>
#include <filesystem>
#include <format>

#include "../include/TSPReader.h"
#include "../include/Instance.h"
#include "../include/NearestNeighborSolver.h"
#include "../include/GreedyCycleSolver.h"
#include "../include/Result.h"
#include "../include/Experiment.h"
#include "../include/RegretSolver.h"

namespace fs = std::filesystem;

int main() {

    fs::path relativeProjectRootDir("../../../");
    const int experiments = 100;
    const int algorithms = 1;
    int d = 0;
    std::string algorithms_names[3] = { "NearestNeighbor", "Regret", "GreedyCycle" };
    std::string datasets[2] = { "kroA100", "kroB100"};
    

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
        std::string json_output = std::to_string(i) + "_" + algorithms_names[j] + "_" + datasets[d] + "_e.json";
        fs::path exportPath = fs::absolute(relativeProjectRootDir / "results" / json_output);
        if (j == 0)
        {
            Result* result1 = solver1.Solve(2);
            length = result1->getRouteLength();
            result1->ExportAsJSON(exportPath);
        }
        else if (j == 1)
        {
            Result* result2 = solver2.Solve(2);
            length = result2->getRouteLength();
            result2->ExportAsJSON(exportPath);
        }
        else if (j == 2)
        {
            Result* result3 = solver3.Solve(2);
            length = result3->getRouteLength();
            result3->ExportAsJSON(exportPath);
        }

        experiment.add_result(j, length, algorithms_names[j], datasets[d]);


    }
    //}


    fs::path ResultExportPath = fs::absolute(relativeProjectRootDir / "results");

    //experiment.show_results();
    experiment.save_results(ResultExportPath);
    
    
    // run python script to draw the graph (the result is both saved in results/plot.png file and displayed on the screen)
    fs::path plotPath = fs::absolute(relativeProjectRootDir / "results" / "plot.png");
    system(std::format("python {} {}", visualizerScriptPath.string(), ResultExportPath.string()).c_str());
    
    return 0;
}
