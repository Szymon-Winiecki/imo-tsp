#pragma once

#include <utility>
#include <vector>
#include <list>

#include "LocalSearch.h"

class Result;
class Instance;


class SteepestLocalSearch : LocalSearch
{
public:
	SteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal) : LocalSearch(initialState, instance, NodeEdgeInternal, (unsigned int)time(NULL)) {}

	SteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal, unsigned int seed) : LocalSearch(initialState, instance, NodeEdgeInternal)
	{
		std::srand(seed);
	}

	Result* Solve();
};