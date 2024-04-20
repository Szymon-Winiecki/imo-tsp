#pragma once

#include <utility>
#include <vector>
#include <list>
#include <queue>

#include "LocalSearch.h"

class Result;
class Instance;
class Move;


class CachedSteepestLocalSearch : LocalSearch
{
public:
	CachedSteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal) : LocalSearch(initialState, instance, NodeEdgeInternal, (unsigned int)time(NULL)) {}

	CachedSteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal, unsigned int seed) : LocalSearch(initialState, instance, NodeEdgeInternal)
	{
		std::srand(seed);
	}

	Result* Solve();

protected:
	void ConstructInitialMoves();
	std::priority_queue<Move*> movesQueue;
};