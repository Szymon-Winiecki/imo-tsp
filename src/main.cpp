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
#include "../include/RegretSolver.h"
#include "../include/RandomSolver.h"
#include "../include/LocalSearch.h"
#include "../include/GreedyLocalSearch.h"
#include "../include/SteepestLocalSearch.h"

namespace fs = std::filesystem;

int main() {
    
    fs::path relativeProjectRootDir("../../../");
    fs::path absoluteDataPath = fs::absolute(relativeProjectRootDir / "data" / "kroA100.tsp");
    TSPReader reader = TSPReader();
    Instance instance = reader.Read(absoluteDataPath);

    std::vector<std::vector<int>> cycles = { { 0, 1 , 6, 7 }, { 2, 3, 4, 5 } };

    RegretSolver solver4 = RegretSolver(&instance);
    Result* result1 = solver4.Solve(2);

    //LocalSearch GreedyLocalSearch(cycles, &instance);

    //Result* r = GreedyLocalSearch.Solve();
    std::cout <<"przed" << result1->getRouteLength() <<std::endl;
    result1->ListToVectors();


    SteepestLocalSearch a = SteepestLocalSearch(result1->GetCycles(), &instance, 0);
    Result* r = a.Solve();
    std::cout << "ppo" << r->getRouteLength() << std::endl;

    //GreedyLocalSearch b = GreedyLocalSearch(result1->GetCycles(), &instance, 1);
    //Result* r2 = b.Solve();
    //std::cout << "ppo" << r2->getRouteLength() << std::endl;




    fs::path ResultExportPath = fs::absolute(relativeProjectRootDir / "results" / "test_export.json");
    

    result1->ExportAsJSON(ResultExportPath);

    fs::path plotPath = fs::absolute(relativeProjectRootDir / "results" / "test.png");
    fs::path visualizerScriptPath = fs::absolute(relativeProjectRootDir / "visualization" / "visualize_single.py");
    system(std::format("python {} {} {}", visualizerScriptPath.string(), ResultExportPath.string(), plotPath.string()).c_str());


    return 0;
    /*

    fs::path relativeProjectRootDir("../../../");
    const int experiments = 1;
    const int algorithms = 4;
    // -1 if all algorithms, if one choose which
    const int alg_num = 3;
    int d = 0;
    

    std::string algorithms_names[4] = { "NearestNeighbor", "Regret", "GreedyCycle","Random"};
    std::string datasets[2] = { "kroA100", "kroB100"};
    

    // read file with the input data
    //fs::path absoluteDataPath = fs::absolute(relativeProjectRootDir / "data" / "test.tsp");
    fs::path absoluteDataPath = fs::absolute(relativeProjectRootDir / "data" / "test.tsp");
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
    RandomSolver solver4 = RandomSolver(&instance);

    int length = 0;
    
    for (int j = 0; j < algorithms; j++)
    {
        if(alg_num != -1)
        {
            if (j != alg_num)
            {
				continue;
			}
	    }
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
        else if (j == 3)
        {
            Result* result4 = solver4.Solve(2);
            length = result4->getRouteLength();
            result4->ExportAsJSON(exportPath);
        }

        experiment.add_result(j, length, algorithms_names[j], datasets[d]);


    }
    }


    fs::path ResultExportPath = fs::absolute(relativeProjectRootDir / "results");

    //experiment.show_results();
    fs::path resultsTxtPat = fs::absolute(relativeProjectRootDir / "results" / "results.txt");
    experiment.save_results(resultsTxtPat);
    
    
    // run python script to draw the graph (the result is both saved in results/plot.png file and displayed on the screen)

    fs::path visualizerScriptPath = fs::absolute(relativeProjectRootDir / "visualization" / "visualize.py");
    system(std::format("python {} {}", visualizerScriptPath.string(), ResultExportPath.string()).c_str());
    
    return 0;*/
}
