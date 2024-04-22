#pragma once

#include <utility>
#include <vector>
#include <list>
#include <queue>
#include <array>

#include "LocalSearch.h"
#include "Instance.h"
#include "MoveComparator.h"

class Result;
class Instance;
class Move;


class CachedSteepestLocalSearch : LocalSearch
{
public:
	CachedSteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance) : CachedSteepestLocalSearch(initialState, instance, (unsigned int)time(NULL)) {}

	CachedSteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, unsigned int seed) : LocalSearch(initialState, instance, 1)
	{
		indexOfNode.resize(instance->Size());

		for (int cycle = 0; cycle < cycles.size(); ++cycle) 
		{
			for (int nodeIndex = 0; nodeIndex < cycles[cycle].size(); ++nodeIndex)
			{
				indexOfNode[cycles[cycle][nodeIndex]] = { cycle, nodeIndex };
			}
		}
	}

	Result* Solve();

protected:
	void ConstructInitialMoves();
	std::priority_queue<Move*, std::vector<Move*>, MoveComparator> movesQueue;

	/*
	* At indexOfNode[n] there is an 2-element array {cycle, index} that indicates cycle in which node n is and its index in that cycle
	*/
	std::vector<std::array<int, 2>> indexOfNode;
};