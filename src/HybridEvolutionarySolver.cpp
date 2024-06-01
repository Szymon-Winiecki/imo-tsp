#include "../include/HybridEvolutionarySolver.h"

#include "../include/EvolutionarySolution.h"
#include "../include/Result.h"
#include  "../include/GreedyLocalSearch.h"
#include  "../include/SteepestLocalSearch.h"

#include <ranges>
#include <stdexcept>
#include <iostream>


template <class LocalSearchAlgorithm, class... LS_Params>
Result* HybridEvolutionarySolver<LocalSearchAlgorithm, LS_Params...>::Solve(int routesNumber)
{
	int iteration = 0;
	uint64_t executionStart = GetCurrentTime();

	InitializePopulation(populationSize, routesNumber);

	std::cout << "Time: " << GetCurrentTime() - executionStart << std::endl;

	while (GetCurrentTime() - executionStart < maxExecutionTime)
	{
		std::array<int, 2> parents = ChooseParents();
		std::shared_ptr<EvolutionarySolution> child = Crossover(population[parents[0]], population[parents[1]]);

		LocalSearchAlgorithm localSearch = LocalSearchAlgorithm(child->cycles, instance, std::get<LS_Params>(params)...);
		child = EvolutionarySolution::FromResult(localSearch.Solve());

		int worstSolutionIndex = 0;
		for (int i = 1; i < population.size(); ++i)
		{
			if (population[i]->GetLength() > population[worstSolutionIndex]->GetLength())
			{
				worstSolutionIndex = i;
			}
		}

		if (child->GetLength() < population[worstSolutionIndex]->GetLength())
		{
			population[worstSolutionIndex] = child;
		}

		++iteration;
	}

	int bestSolutionIndex = 0;
	for (int i = 1; i < population.size(); ++i)
	{
		if (population[i]->GetLength() < population[bestSolutionIndex]->GetLength())
		{
			bestSolutionIndex = i;
		}
	}

	std::cout << "HEA Iterations: " << iteration << std::endl;

	return population[bestSolutionIndex]->GetResult();
	
}

template<class LocalSearchAlgorithm, class ...LS_Params>
void HybridEvolutionarySolver<LocalSearchAlgorithm, LS_Params...>::Solve(std::vector<std::list<int>>& routes)
{
	throw std::runtime_error("Not implemented");
}

template<class LocalSearchAlgorithm, class ...LS_Params>
void HybridEvolutionarySolver<LocalSearchAlgorithm, LS_Params...>::InitializePopulation(int populationSize, int routesNumber)
{
	population.clear();
	population.reserve(populationSize);
	for (int i = 0; i < populationSize; ++i)
	{
		Result* initialSolution = initialSolutionGenerator->Solve(routesNumber);
		LocalSearchAlgorithm localSearch = LocalSearchAlgorithm(initialSolution->GetCycles(), instance, std::get<LS_Params>(params)...);
		initialSolution = localSearch.Solve();
		population.push_back(std::make_shared<EvolutionarySolution>(instance, initialSolution->GetCycles()));
	}
}

template<class LocalSearchAlgorithm, class ...LS_Params>
std::array<int, 2> HybridEvolutionarySolver<LocalSearchAlgorithm, LS_Params...>::ChooseParents()
{
	int parentA = RandomInt(0, populationSize);

	int parentB = RandomInt(0, populationSize);
	while (parentB == parentA)
	{
		parentB = RandomInt(0, populationSize);
	}

	return {parentA, parentB};
}

template<class LocalSearchAlgorithm, class ...LS_Params>
std::shared_ptr<EvolutionarySolution> HybridEvolutionarySolver<LocalSearchAlgorithm, LS_Params...>::Crossover(std::shared_ptr<EvolutionarySolution> parentA, std::shared_ptr<EvolutionarySolution> parentB)
{
	std::vector<std::list<int>> childRoutes;

	childRoutes.resize(parentA->cycles.size());

	for (int i = 0; i < parentA->cycles.size(); ++i)
	{
		int lastAddedNode = -1;
		int lastNode = parentA->cycles[i].back();

		for (auto node : parentA->cycles[i])
		{
			if (parentB->HasEdge(lastNode, node))
			{
				if (lastAddedNode != lastNode)
				{
					childRoutes[i].push_back(lastNode);
				}
				childRoutes[i].push_back(node);
				lastAddedNode = node;
			}

			lastNode = node;
		}
	}

	reconstructionHeuristic->Solve(childRoutes);


	std::vector<std::vector<int>> childCycles;
	childCycles.resize(childRoutes.size());
	for (int i = 0; i < childRoutes.size(); ++i)
	{
		childCycles[i] = childRoutes[i] | std::ranges::to<std::vector>();
	}

	return std::make_shared<EvolutionarySolution>(instance, childCycles);
}

template class HybridEvolutionarySolver<GreedyLocalSearch, int>;
template class HybridEvolutionarySolver<SteepestLocalSearch, int>;
