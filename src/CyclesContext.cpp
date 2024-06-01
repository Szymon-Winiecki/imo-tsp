#include "../include/CyclesContext.h"

#include <algorithm>

CyclesContext::CyclesContext(Instance* instance, std::vector<std::vector<int>>& cycles, std::vector<std::array<int, 2>>& indexOfNode)
	: instance{ instance }, cycles{ cycles }, indexOfNode{ indexOfNode }
{

}

Instance* CyclesContext::GetInstance() const
{
	return instance;
}

int CyclesContext::NodeAt(int cycle, int nodeIndex) const
{
	return cycles[cycle][nodeIndex];
}

int CyclesContext::NodeCycle(int node) const
{
	return indexOfNode[node][0];
}

int CyclesContext::NodeIndex(int node) const
{
	return indexOfNode[node][1];
}

int CyclesContext::NextNodeIndex(int cycle, int nodeIndex) const
{
	return nodeIndex < cycles[cycle].size() - 1 ? (nodeIndex + 1) : 0;
}

int CyclesContext::PrevNodeIndex(int cycle, int nodeIndex) const
{
	return nodeIndex > 0 ? (nodeIndex - 1) : cycles[cycle].size() - 1;
}

int CyclesContext::NextNode(int cycle, int nodeIndex) const
{
	return cycles[cycle][NextNodeIndex(cycle, nodeIndex)];
}

int CyclesContext::NextNode(int node) const
{
	return NextNode(indexOfNode[node][0], indexOfNode[node][1]);
}

int CyclesContext::PrevNode(int cycle, int nodeIndex) const
{
	return cycles[cycle][PrevNodeIndex(cycle, nodeIndex)];
}

int CyclesContext::PrevNode(int node) const
{
	return PrevNode(indexOfNode[node][0], indexOfNode[node][1]);
}

int CyclesContext::DistanceToNeighbours(int cycle, int nodeIndex) const
{
	return instance->Distance(cycles[cycle][PrevNodeIndex(cycle, nodeIndex)], cycles[cycle][nodeIndex]) + instance->Distance(cycles[cycle][nodeIndex], cycles[cycle][NextNodeIndex(cycle, nodeIndex)]);
}

int CyclesContext::EdgeLength(int cycle, int EdgeIndex) const
{
	return instance->Distance(cycles[cycle][EdgeIndex], cycles[cycle][NextNodeIndex(cycle, EdgeIndex)]);
}

bool CyclesContext::IsNeighbourhood(int node, int neighA, int neighB) const
{
	if (
		neighA != PrevNode(node) &&
		neighA != NextNode(node)
		)
	{
		return false; //neighA is not a neighbour of the node
	}

	if (
		neighB != PrevNode(node) &&
		neighB != NextNode(node)
		)
	{
		return false; //neighB is not a neighbour of the node
	}

	return true;
}

bool CyclesContext::IsEdge(int edgeStart, int edgeEnd) const
{
	return NextNode(edgeStart) == edgeEnd;
}

bool CyclesContext::IsEdgeOrReversedEdge(int edgeStart, int edgeEnd) const
{
	return NextNode(edgeStart) == edgeEnd || NextNode(edgeEnd) == edgeStart;
}

int CyclesContext::EdgeSwapGain(int cycle, int edgeAIndex, int edgeBIndex)
{
	if (edgeAIndex > edgeBIndex)
	{
		std::swap(edgeAIndex, edgeBIndex);
	}

	int currentDistance = EdgeLength(cycle, edgeAIndex) + EdgeLength(cycle, edgeBIndex);
	int distanceAfterSwap = instance->Distance(cycles[cycle][edgeAIndex], cycles[cycle][edgeBIndex]) + instance->Distance(cycles[cycle][NextNodeIndex(cycle, edgeAIndex)], cycles[cycle][NextNodeIndex(cycle, edgeBIndex)]);
	return currentDistance - distanceAfterSwap;
}

int CyclesContext::EdgeSwapGain(int edgeAStart, int edgeAEnd, int edgeBStart, int edgeBEnd)
{
	int currentDistance = instance->Distance(edgeAStart, edgeAEnd) + instance->Distance(edgeBStart, edgeBEnd);
	int distanceAfterSwap = instance->Distance(edgeAStart, edgeBStart) + instance->Distance(edgeAEnd, edgeBEnd);
	return currentDistance - distanceAfterSwap;
}

int CyclesContext::NodeSwapGain(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
{
	int currentDistance = DistanceToNeighbours(cycleA, nodeAIndex) + DistanceToNeighbours(cycleB, nodeBIndex);

	NodeSwap(cycleA, nodeAIndex, cycleB, nodeBIndex);

	int distanceAfterSwap = DistanceToNeighbours(cycleA, nodeAIndex) + DistanceToNeighbours(cycleB, nodeBIndex);

	NodeSwap(cycleA, nodeAIndex, cycleB, nodeBIndex);


	return currentDistance - distanceAfterSwap;
}

void CyclesContext::EdgeSwap(int cycle, int edgeAIndex, int edgeBIndex)
{
	if (edgeAIndex > edgeBIndex)
	{
		std::swap(edgeAIndex, edgeBIndex);
	}


	int i = edgeAIndex + 1;
	int j = edgeBIndex;
	while (i < j)
	{
		std::swap(indexOfNode[cycles[cycle][i++]], indexOfNode[cycles[cycle][j--]]);
	}

	std::reverse(cycles[cycle].begin() + edgeAIndex + 1, cycles[cycle].begin() + edgeBIndex + 1);
}

void CyclesContext::EdgeSwap(int edgeAStart, int edgeBStart)
{
	EdgeSwap(indexOfNode[edgeAStart][0], indexOfNode[edgeAStart][1], indexOfNode[edgeBStart][1]);
}

void CyclesContext::NodeSwap(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
{
	std::swap(indexOfNode[cycles[cycleA][nodeAIndex]], indexOfNode[cycles[cycleB][nodeBIndex]]);
	std::swap(cycles[cycleA][nodeAIndex], cycles[cycleB][nodeBIndex]);
}

void CyclesContext::NodeSwap(int nodeA, int nodeB)
{
	NodeSwap(indexOfNode[nodeA][0], indexOfNode[nodeA][1], indexOfNode[nodeB][0], indexOfNode[nodeB][1]);
}
