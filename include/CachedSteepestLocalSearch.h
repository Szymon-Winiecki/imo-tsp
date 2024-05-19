#pragma once

#include <utility>
#include <vector>
#include <list>
#include <queue>
#include <array>
#include <memory>

#include "LocalSearch.h"
#include "Instance.h"
#include "MoveComparator.h"

class Result;
class Instance;
class Move;


class CachedSteepestLocalSearch : public LocalSearch
{
public:
	CachedSteepestLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance) : LocalSearch(initialState, instance)
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
	std::priority_queue<std::shared_ptr<Move>, std::vector<std::shared_ptr<Move>>, MoveComparator> movesQueue;

	/*
	* At indexOfNode[n] there is an 2-element array {cycle, index} that indicates cycle in which node n is and its index in that cycle
	*/
	std::vector<std::array<int, 2>> indexOfNode;
};