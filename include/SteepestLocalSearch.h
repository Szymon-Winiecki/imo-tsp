#pragma once

#include <utility>
#include <vector>
#include <list>

#include "LocalSearch.h"

class Result;
class Instance;


class SteepestLocalSearch : public LocalSearch
{
public:
	SteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance) : SteepestLocalSearch(initialState, instance, 0) {}

	SteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal) : LocalSearch(initialState, instance), NodeEdgeInternal{ NodeEdgeInternal } { }

	Result* Solve();

protected:
	int NodeEdgeInternal;
};