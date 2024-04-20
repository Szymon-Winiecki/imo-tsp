#include "../include/CyclesContext.h"

#include <algorithm>

CyclesContext::CyclesContext(Instance* intance, std::vector<std::vector<int>>& cycles)
	: instance{ instance }, cycles{ cycles }
{}

int CyclesContext::NodeAt(int cycle, int nodeIndex)
{
	return cycles[cycle][nodeIndex];
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

int CyclesContext::PrevNode(int cycle, int nodeIndex) const
{
	return cycles[cycle][PrevNodeIndex(cycle, nodeIndex)];
}

int CyclesContext::DistanceToNeighbours(int cycle, int nodeIndex) const
{
	return instance->Distance(cycles[cycle][PrevNodeIndex(cycle, nodeIndex)], cycles[cycle][nodeIndex]) + instance->Distance(cycles[cycle][nodeIndex], cycles[cycle][NextNodeIndex(cycle, nodeIndex)]);
}

int CyclesContext::EdgeLength(int cycle, int EdgeIndex) const
{
	return instance->Distance(cycles[cycle][EdgeIndex], cycles[cycle][NextNodeIndex(cycle, EdgeIndex)]);
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

	std::reverse(cycles[cycle].begin() + edgeAIndex + 1, cycles[cycle].begin() + edgeBIndex + 1);
}

void CyclesContext::NodeSwap(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
{
	int nodeA = cycles[cycleA][nodeAIndex];
	cycles[cycleA][nodeAIndex] = cycles[cycleB][nodeBIndex];
	cycles[cycleB][nodeBIndex] = nodeA;
}
