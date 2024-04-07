#include "LocalSearch.h"

#include "../include/LocalSearch.h"
#include "../include/Result.h"
#include "../include/Instance.h"

#include <iostream>
#include <algorithm>

Result* LocalSearch::Solve()
{

	int gain = ExternalNodeSwapGain(0, 1, 1, 3);
	ExternalNodeSwap(0, 1, 1, 3);

	gain = InternalEdgeSwapGain(0, 0, 2);
	InternalEdgeSwap(0, 0, 2);

	std::cout << "GAIN: " << gain << std::endl;

	Result* result = new Result(instance, cycles.size());

	for (int i = 0; i < cycles.size(); ++i)
	{
		int lastNode = -1;

		for (auto node : cycles[i])
		{
			if (lastNode != -1)
			{
				result->AddEdge(i, lastNode, node);
			}
			lastNode = node;
		}
		result->AddEdge(i, lastNode, cycles[i].front());
	}

	return result;
}

int LocalSearch::NextNodeIndex(int cycle, int nodeIndex) const
{
	return nodeIndex < cycles[cycle].size() - 1 ? (nodeIndex + 1) : 0;
}

int LocalSearch::PrevNodeIndex(int cycle, int nodeIndex) const
{
	return nodeIndex > 0 ? (nodeIndex - 1) : cycles[cycle].size() - 1;
}

int LocalSearch::DistanceToNeighbours(int cycle, int nodeIndex) const
{
	return instance->Distance(cycles[cycle][PrevNodeIndex(cycle, nodeIndex)], cycles[cycle][nodeIndex]) + instance->Distance(cycles[cycle][nodeIndex], cycles[cycle][NextNodeIndex(cycle, nodeIndex)]);
}

int LocalSearch::EdgeLength(int cycle, int EdgeIndex) const
{
	return instance->Distance(cycles[cycle][EdgeIndex], cycles[cycle][NextNodeIndex(cycle, EdgeIndex)]);
}

int LocalSearch::InternalNodeSwapGain(int cycle, int nodeAIndex, int nodeBIndex)
{

	int currentDistance = DistanceToNeighbours(cycle, nodeAIndex) + DistanceToNeighbours(cycle, nodeBIndex);

	InternalNodeSwap(cycle, nodeAIndex, nodeBIndex);

	int distanceAfterSwap = DistanceToNeighbours(cycle, nodeAIndex) + DistanceToNeighbours(cycle, nodeBIndex);

	InternalNodeSwap(cycle, nodeAIndex, nodeBIndex);

	return currentDistance - distanceAfterSwap;
}

int LocalSearch::InternalEdgeSwapGain(int cycle, int edgeAIndex, int edgeBIndex)
{
	if (edgeAIndex > edgeBIndex)
	{
		std::swap(edgeAIndex, edgeBIndex);
	}

	int currentDistance = EdgeLength(cycle, edgeAIndex) + EdgeLength(cycle, edgeBIndex);
	int distanceAfterSwap = instance->Distance(cycles[cycle][edgeAIndex], cycles[cycle][edgeBIndex]) + instance->Distance(cycles[cycle][NextNodeIndex(cycle, edgeAIndex)], cycles[cycle][NextNodeIndex(cycle, edgeBIndex)]);
	return currentDistance - distanceAfterSwap;
}

int LocalSearch::ExternalNodeSwapGain(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
{
	int currentDistance = DistanceToNeighbours(cycleA, nodeAIndex) + DistanceToNeighbours(cycleB, nodeBIndex);

	ExternalNodeSwap(cycleA, nodeAIndex, cycleB, nodeBIndex);

	int distanceAfterSwap = DistanceToNeighbours(cycleA, nodeAIndex) + DistanceToNeighbours(cycleB, nodeBIndex);

	ExternalNodeSwap(cycleA, nodeAIndex, cycleB, nodeBIndex);


	return currentDistance - distanceAfterSwap;
}

void LocalSearch::InternalNodeSwap(int cycle, int nodeAIndex, int nodeBIndex)
{
	int nodeA = cycles[cycle][nodeAIndex];
	cycles[cycle][nodeAIndex] = cycles[cycle][nodeBIndex];
	cycles[cycle][nodeBIndex] = nodeA;
}

void LocalSearch::InternalEdgeSwap(int cycle, int edgeAIndex, int edgeBIndex)
{
	if (edgeAIndex > edgeBIndex)
	{
		std::swap(edgeAIndex, edgeBIndex);
	}

	std::reverse(cycles[cycle].begin() + edgeAIndex + 1, cycles[cycle].begin() + edgeBIndex + 1);
}

void LocalSearch::ExternalNodeSwap(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
{
	int nodeA = cycles[cycleA][nodeAIndex];
	cycles[cycleA][nodeAIndex] = cycles[cycleB][nodeBIndex];
	cycles[cycleB][nodeBIndex] = nodeA;
}