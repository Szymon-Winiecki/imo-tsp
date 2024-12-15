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

namespace fs = std::filesystem;

int main() {
    srand(time(NULL));

    /*
    * Set up paths
	*/
	fs::path relativeProjectRootDir("../../../");   // root dir relative to the location of the executable
	fs::path absoluteDataDir = fs::absolute(relativeProjectRootDir / "data");   // direcory with data(problem instances) files
	fs::path absouluteResultsDir = fs::absolute(relativeProjectRootDir / "results");   // results directory (for saving json and plot)
	fs::path visualizerScriptPath = fs::absolute(relativeProjectRootDir / "visualization" / "visualize_single.py");   // python script for route visualization

    /*
    * 
    */
	std::string dataFileName = "kroA200.tsp";       // name of the file with the problem instance (must be in the data directory)
	std::string exportFileName = "kroA200.json";    // how to name the exported json file
	std::string plotFileName = "kroA200.png";       // how to name the plot file

    /*
	* Read the instance
    */
    TSPReader reader = TSPReader();
    Instance instance = reader.Read(absoluteDataDir / dataFileName);

    /*
    * EXAMPLE 1.
    * How to use IteratedLocalSearch
    */

    Solver* initialSolver = new GreedyCycleSolver(&instance);       // solver to generate initial solution
    Perturbator* perturbator = new RandomPerturbator(10);           // perturbator for perturbating the solution
    uint64_t maxExecutionTime = 2000;                               // maximum execution time in milliseconds

    Result* initialSolution = initialSolver->Solve();
    IteratedLocalSearch<GreedyLocalSearch, MoveType> ILSolver = IteratedLocalSearch<GreedyLocalSearch, MoveType>(initialSolution->GetCycles(), &instance, perturbator, maxExecutionTime, MoveType::InternalEdgeSwap);
    Result* finalResult = ILSolver.Solve();


    /*
    * EXAMPLE 2.
	* How to use HybridEvolutionarySolver
    */
    
    /*
	Solver* randomSolver = new RandomSolver(&instance);             // solver for generating initial solutions
	Solver* repairSolver = new NearestNeighborSolver(&instance);    // solver for repairing crossovered solutions
	int populationSize = 20;                                        // size of the population
	uint64_t maxExecutionTime = 5000;                               // maximum execution time in milliseconds
    
    HybridEvolutionarySolver<SteepestLocalSearch, MoveType> HEsolver = HybridEvolutionarySolver<SteepestLocalSearch, MoveType>(&instance, randomSolver, repairSolver, populationSize, maxExecutionTime, MoveType::InternalEdgeSwap);
    Result* finalResult = HEsolver.Solve();
    */


    /*
	* Saving the results
    */

	std::cout << "Total routes length: " << finalResult->getRouteLength() << std::endl;

	// Create results directory if it does not exist
    if (!fs::is_directory(absouluteResultsDir) || !fs::exists(absouluteResultsDir)) {
        fs::create_directory(absouluteResultsDir);
    }

	// export results to json
    fs::path ResultExportPath = absouluteResultsDir / exportFileName;
    finalResult->ExportAsJSON(ResultExportPath);

	// run python script to draw the plot
    fs::path plotPath = absouluteResultsDir / plotFileName;
    system(std::format("python {} {} {}", visualizerScriptPath.string(), ResultExportPath.string(), plotPath.string()).c_str());

    return 0;
}
