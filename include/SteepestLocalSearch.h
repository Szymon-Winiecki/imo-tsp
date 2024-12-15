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
	SteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance) : SteepestLocalSearch(initialState, instance, MoveType::InternalNodeSwap) {}

	SteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, MoveType NodeEdgeInternal) : LocalSearch(initialState, instance), InternalMoveType{ NodeEdgeInternal } { }

	Result* Solve();

protected:
	MoveType InternalMoveType;
};