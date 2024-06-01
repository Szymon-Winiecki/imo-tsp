#pragma once


#include "Solver.h"
#include "LocalSearch.h"

#include <tuple>
#include <memory>
#include <array>

class Result;
class EvolutionarySolution;

template <class LocalSearchAlgorithm, class... LS_Params>
class HybridEvolutionarySolver : public Solver
{
public:
	HybridEvolutionarySolver(Instance* instance, Solver* initialSolutionGenerator, Solver* reconstructionHeuristic, int popultionSize, uint64_t maxExecutionTime, LS_Params&&... LS_parameters)
		: Solver(instance),
		initialSolutionGenerator(initialSolutionGenerator),
		reconstructionHeuristic(reconstructionHeuristic),
		populationSize(popultionSize),
		maxExecutionTime(maxExecutionTime)
	{
		static_assert(std::is_base_of<LocalSearch, LocalSearchAlgorithm>::value, "T must inherit from LocalSearch");

		params = std::make_tuple(std::move(LS_parameters)...);
	}

	Result* Solve(int routesNumber = 2) override;
	void Solve(std::vector<std::list<int>>& routes) override;

protected:
	void InitializePopulation(int populationSize, int routesNumber);

	std::array<int, 2> ChooseParents();
	std::shared_ptr<EvolutionarySolution> Crossover(std::shared_ptr<EvolutionarySolution> parentA, std::shared_ptr<EvolutionarySolution> parentB);

	Solver* initialSolutionGenerator;
	Solver* reconstructionHeuristic;

	int populationSize;
	std::vector<std::shared_ptr<EvolutionarySolution>> population;

	uint64_t maxExecutionTime;

	std::tuple<LS_Params...> params;
};