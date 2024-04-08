#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>

class Result;
class Instance;

enum class MoveType
{
	InternalEdgeSwap, InternalNodeSwap, ExternalNodeSwap
};

class LocalSearch
{
public:
	LocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal) : LocalSearch(initialState, instance, NodeEdgeInternal, (unsigned int)time(NULL)) {}

	LocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, int NodeEdgeInternal, unsigned int seed) : cycles{ initialState }, instance{ instance }, NodeEdgeInternal{ NodeEdgeInternal }
	{
		std::srand(seed);
	}

	Result* Solve();

protected:

	int NextNodeIndex(int cycle, int nodeIndex) const;
	int PrevNodeIndex(int cycle, int nodeIndex) const;
	int DistanceToNeighbours(int cycle, int nodeIndex) const;
	int EdgeLength(int cycle, int EdgeIndex) const;

	int InternalNodeSwapGain(int cycle, int nodeAIndex, int nodeBIndex);
	int InternalEdgeSwapGain(int cycle, int edgeAIndex, int edgeBIndex);
	int ExternalNodeSwapGain(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex);

	void InternalNodeSwap(int cycle, int nodeAIndex, int nodeBIndex);
	void InternalEdgeSwap(int cycle, int edgeAIndex, int edgeBIndex);
	void ExternalNodeSwap(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex);

	std::vector<std::vector<int>> cycles;
	Instance* instance;
	int NodeEdgeInternal;
};