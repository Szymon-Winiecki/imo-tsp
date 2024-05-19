#include "../include/DestroyRepairPerturbator.h"

#include "../include/NearestNeighborSolver.h"

#include <algorithm>
#include <ranges>

#include <iostream>

void DestroyRepairPerturbator::Perturbate(std::vector<std::vector<int>>& cycles)
{
	std::vector<std::list<int>> destroyedCycles;

	for (int i = 0; i < cycles.size(); ++i)
	{
		int cutStart = rand() % cycles[i].size();

		destroyedCycles.push_back(Destroy(cycles, i, cutStart, numChanges));
	}

	solver->Solve(destroyedCycles);

	//std::vector<std::vector<int>> newCycles(cycles.size());

	for (int i = 0; i < cycles.size(); ++i)
	{
		cycles[i] = destroyedCycles[i] | std::ranges::to<std::vector>();
	}
}

std::list<int> DestroyRepairPerturbator::Destroy(std::vector<std::vector<int>>& cycles, int cycle, int cutStart, int cutLength)
{
	std::list<int> destroyedCycle;

	int nextNode = std::max(0, (cutStart + cutLength) - (int)cycles[cycle].size());

	while (nextNode < cutStart)
	{
		destroyedCycle.push_back(cycles[cycle][nextNode++]);
	}
	nextNode += cutLength;
	while (nextNode < cycles[cycle].size())
	{
		destroyedCycle.push_back(cycles[cycle][nextNode++]);
	}

	return destroyedCycle;
}
