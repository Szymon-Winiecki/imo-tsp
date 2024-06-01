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
#include "../include/CachedSteepestLocalSearch.h"
#include "../include/RandomWalk.h"
#include "../include/IteratedLocalSearch.h"
#include "../include/RandomPerturbator.h"
#include "../include/DestroyRepairPerturbator.h"
#include "../include/LargeScaleNeighborhoodSearch.h"
#include "../include/HybridEvolutionarySolver.h"

#define NODE_SWAP 0
#define EDGE_SWAP 1

namespace fs = std::filesystem;

int main() {
    srand(time(NULL));

    fs::path relativeProjectRootDir("../../../");
    fs::path absoluteDataPath = fs::absolute(relativeProjectRootDir / "data" / "kroA200.tsp");
    TSPReader reader = TSPReader();
    Instance instance = reader.Read(absoluteDataPath);

    //std::vector<std::vector<int>> cycles = { { 0, 1 , 6, 7 }, { 2, 3, 4, 5 } };

    RandomSolver* randomSolver = new RandomSolver(&instance);
    Solver* repairSolver = new NearestNeighborSolver(&instance);
    
    HybridEvolutionarySolver<SteepestLocalSearch, int> HEsolver = HybridEvolutionarySolver<SteepestLocalSearch, int>(&instance, randomSolver, repairSolver, 20, 20000, EDGE_SWAP);

    
    Result* finalResult = HEsolver.Solve();
	std::cout << "Final result: " << finalResult->getRouteLength() << std::endl;


    //GreedyLocalSearch b = GreedyLocalSearch(result1->GetCycles(), &instance, 1);
    //Result* r2 = b.Solve();
    //std::cout << "ppo" << r2->getRouteLength() << std::endl;


    fs::path ResultExportPath = fs::absolute(relativeProjectRootDir / "results" / "test_export.json");
    

    finalResult->ExportAsJSON(ResultExportPath);

    fs::path plotPath = fs::absolute(relativeProjectRootDir / "results" / "test.png");
    fs::path visualizerScriptPath = fs::absolute(relativeProjectRootDir / "visualization" / "visualize_single.py");
    system(std::format("python {} {} {}", visualizerScriptPath.string(), ResultExportPath.string(), plotPath.string()).c_str());


    return 0;
    /*
    srand(time(NULL));
    fs::path relativeProjectRootDir("../../../");
    const int experiments = 100;
    const int algorithms = 4;
    // -1 if all algorithms, if one choose which
    const int alg_num = -1;
    const int localSearch = 4;
    const int InternalType = 2;
    int d = 1;
    

    std::string algorithms_names[4] = { "NearestNeighbor", "Regret", "GreedyCycle", "Random"};
    std::string datasets[2] = { "kroA200", "kroB200"};
    std::string localSearchTypes[4] = { "Steepest", "Greedy", "RandomWalk", "CachedSteepest"};
    std::string InternalTypes[2] = { "Node", "Edge" };

    // read file with the input data
    fs::path absoluteDataPath = fs::absolute(relativeProjectRootDir / "data" / "kroB200.tsp");
    //fs::path absoluteDataPath = fs::absolute(relativeProjectRootDir / "data" / "test.tsp");
    TSPReader reader = TSPReader();
    Instance instance = reader.Read(absoluteDataPath);
    Experiment experiment = Experiment(algorithms);

    // create results directory, if not exists
    if (!fs::is_directory(relativeProjectRootDir / "results") || !fs::exists(relativeProjectRootDir / "results")) {
        fs::create_directory(relativeProjectRootDir / "results");
    }
    experiment.resizer(100);
    // run solver
    NearestNeighborSolver solver1 = NearestNeighborSolver(&instance);
    RegretSolver solver2 = RegretSolver(&instance);
    GreedyCycleSolver solver3 = GreedyCycleSolver(&instance);
    int s = rand() % 10000;
    RandomSolver solver4 = RandomSolver(&instance, s);

    int length = 0;
    int type = 0;
    float time = 0;
    
    /*for (int i = 0; i < 100; i++)
    {
        std::string json_output = std::to_string(i) + "_" + algorithms_names[0] + "_" + datasets[d] + "_" + "_" + "_e.json";
        fs::path exportPath = fs::absolute(relativeProjectRootDir / "results" / json_output);
        auto start = std::chrono::steady_clock::now();
        Result* result;
        result = solver3.Solve(2);
        length = result->getRouteLength();
        
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << algorithms_names[0] << " " << 0 << " " << 0 << " " << 0 << " " << length << " Czas" << duration.count() << std::endl;
        time = duration.count() / 10000;
        experiment.add_result(type, length, algorithms_names[0], datasets[d], "", "", time);
        result->ExportAsJSON(exportPath);
    }*/
    
    /*
    for (int j = 0; j < algorithms; j++)
    {
        if (j != 3) continue;
        //j: NearestNeighbor - 0, Regret - 1, GreedyCycle - 2, Random - 3
        for (int k = 0; k < InternalType; k++)
        {
            if (k != 1) continue;

            //k: node - 0 , edge - 1
            for (int i = 0; i < experiments; i++)
            {
                Result* result;
                if (j == 0)
                {
                    result = solver1.Solve(2);
                }
                else if (j == 1)
                {
                    result = solver2.Solve(2);
                }
                else if (j == 2)
                {
                    result = solver3.Solve(2);
                }
                else if (j == 3)
                {
                    s++;
                    RandomSolver solver4 = RandomSolver(&instance, s);
                    result = solver4.Solve(2);
                }

                result->ListToVectors();
                for (int ls = 0; ls < localSearch; ls++)
                {
                    if (ls != 3) continue;
                    //ls: Steepest - 0, Greedy - 1, RandomWalk - 2, CachedSteepest - 3
                    auto start = std::chrono::steady_clock::now();
                    // eksperyment_nazwaAlgorytmu_nazwaDatasetu_typWyszukiwaniaLokalnego_TypWewnetrznejZamiany_e.json
                    std::string json_output = std::to_string(i) + "_" + algorithms_names[j] + "_" + datasets[d] + "_" + localSearchTypes[ls] + "_" + InternalTypes[k] + "_e.json";
                    fs::path exportPath = fs::absolute(relativeProjectRootDir / "results" / json_output);
                    if (ls == 0)
                    {
                        SteepestLocalSearch a = SteepestLocalSearch(result->GetCycles(), &instance, k);
                        Result* r = a.Solve();
                        length = r->getRouteLength();
                        r->ExportAsJSON(exportPath);
                    }
                    if (ls == 1)
                    {
                        s++;
                        GreedyLocalSearch a = GreedyLocalSearch(result->GetCycles(), &instance, k, s);
                        Result* r = a.Solve();
                        length = r->getRouteLength();
                        r->ExportAsJSON(exportPath);
                    }
                    if (ls == 2)
                    {
                    	RandomWalk a = RandomWalk(result->GetCycles(), &instance, 0.0427);
                        
						Result* r = a.Solve();
						length = r->getRouteLength();
						r->ExportAsJSON(exportPath);
                    }
                    if (ls == 3)
                    {
                        CachedSteepestLocalSearch a = CachedSteepestLocalSearch(result->GetCycles(), &instance);

                        Result* r = a.Solve();
                        length = r->getRouteLength();
                        r->ExportAsJSON(exportPath);
                    }

                    auto end = std::chrono::steady_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
                    std::cout << algorithms_names[j] << " " << datasets[d] << " " << localSearchTypes[ls] << " " << InternalTypes[k] << " " << length << " Czas" << duration.count() << std::endl;
                    time = duration.count() / 10000;
                    experiment.add_result(0, length, algorithms_names[j], datasets[d], localSearchTypes[ls], InternalTypes[k], time);
                }
            }
        }
    }


    fs::path ResultExportPath = fs::absolute(relativeProjectRootDir / "results");

    //experiment.show_results();
    fs::path resultsTxtPat = fs::absolute(relativeProjectRootDir / "results" / "results.txt");
    experiment.save_results(resultsTxtPat);
    
    
    // run python script to draw the graph (the result is both saved in results/plot.png file and displayed on the screen)

    fs::path visualizerScriptPath = fs::absolute(relativeProjectRootDir / "visualization" / "visualize.py");
    system(std::format("python {} {}", visualizerScriptPath.string(), ResultExportPath.string()).c_str());
    
    return 0;
    */
}
