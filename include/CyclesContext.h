#pragma once

#include "Instance.h"
#include <vector>

class CyclesContext
{
public:
	CyclesContext(Instance* instance, std::vector<std::vector<int>>& cycles, std::vector<std::array<int, 2>>& indexOfNode);

	int NodeAt(int cycle, int nodeIndex) const;
	int NodeCycle(int node) const;
	int NodeIndex(int node) const;

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
	* Get the successor of the node
	*/
	int NextNode(int node) const;

	/*
	* Get the predecessor of node at nodeIndex position in the cycle
	*/
	int PrevNode(int cycle, int nodeIndex) const;

	/*
	* Get the predecessor of the node
	*/
	int PrevNode(int node) const;

	int DistanceToNeighbours(int cycle, int nodeIndex) const;
	int EdgeLength(int cycle, int EdgeIndex) const;

	bool IsNeighbourhood(int node, int neighA, int neighB) const;
	bool IsEdge(int edgeStart, int edgeEnd) const;
	bool IsEdgeOrReversedEdge(int edgeStart, int edgeEnd) const;

	int EdgeSwapGain(int cycle, int edgeAIndex, int edgeBIndex);
	int EdgeSwapGain(int edgeAStart, int edgeAEnd, int edgeBStart, int edgeBEnd);

	int NodeSwapGain(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex);

	void EdgeSwap(int cycle, int edgeAIndex, int edgeBIndex);
	void EdgeSwap(int edgeAStart, int edgeBStart);

	void NodeSwap(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex);
	void NodeSwap(int nodeA, int nodeB);

private:
	Instance* instance;
	std::vector<std::vector<int>>& cycles;

	/*
	* At indexOfNode[n] there is an 2-element array {cycle, index} that indicates cycle in which node n is and its index in that cycle
	*/
	std::vector<std::array<int, 2>>& indexOfNode;
};