#pragma once

#include <utility>
#include <vector>
#include <list>

#include "LocalSearch.h"

class Result;
class Instance;


class GreedyLocalSearch: public LocalSearch
{
	public:
	GreedyLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance) : GreedyLocalSearch(initialState, instance, 0) {}

	GreedyLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal) : LocalSearch(initialState, instance), NodeEdgeInternal{ NodeEdgeInternal } { }

	Result* Solve();

	protected:
		std::pair<int, int> FindBestChange(const std::list<int>& route, const std::vector<bool>& usedNodes) const;

		int NodeEdgeInternal;
};