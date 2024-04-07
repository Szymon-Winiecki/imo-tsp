#pragma once

#include <utility>
#include <vector>
#include <list>

#include "LocalSearch.h"

class Result;
class Instance;


class GreedyLocalSearch: LocalSearch
{
	public:
	GreedyLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal) : LocalSearch(initialState, instance, NodeEdgeInternal, (unsigned int)time(NULL)) {}

	GreedyLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal, unsigned int seed) : LocalSearch(initialState, instance, NodeEdgeInternal)
	{
		std::srand(seed);
	}

	Result* Solve();

	protected:
		std::pair<int, int> FindBestChange(const std::list<int>& route, const std::vector<bool>& usedNodes) const;
};