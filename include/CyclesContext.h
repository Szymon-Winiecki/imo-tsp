#pragma once

#include "Instance.h"
#include <vector>

class CyclesContext
{
public:
	CyclesContext(Instance* intance, std::vector<std::vector<int>>& cycles);

	int NodeAt(int cycle, int nodeIndex);

	/*
	* Get index of the successor of node at nodeIndex position in the cycle
	*/
	int NextNodeIndex(int cycle, int nodeIndex) const;

	/*
	* Get index of the predecessor of node at nodeIndex position in the cycle
	*/
	int PrevNodeIndex(int cycle, int nodeIndex) const;

	/*
	* Get the successor of node at nodeIndex position in the cycle
	*/
	int NextNode(int cycle, int nodeIndex) const;

	/*
	* Get the predecessor of node at nodeIndex position in the cycle
	*/
	int PrevNode(int cycle, int nodeIndex) const;

	int DistanceToNeighbours(int cycle, int nodeIndex) const;
	int EdgeLength(int cycle, int EdgeIndex) const;

	int EdgeSwapGain(int cycle, int edgeAIndex, int edgeBIndex);
	int NodeSwapGain(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex);

	void EdgeSwap(int cycle, int edgeAIndex, int edgeBIndex);
	void NodeSwap(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex);
private:
	Instance* instance;
	std::vector<std::vector<int>>& cycles;
};