#include "LocalSearch.h"

#include "../include/LocalSearch.h"
#include "../include/Result.h"
#include "../include/Instance.h"

#include <iostream>

Result* LocalSearch::Solve()
{

	int gain = ExternalNodeSwapGain(0, 1, 1, 3);
	ExternalNodeSwap(0, 1, 1, 3);

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

int LocalSearch::InternalNodeSwapGain(int cycle, int nodeAIndex, int nodeBIndex)
{
	//std::cout << "Swap gain " << cycles[cycle][nodeAIndex] << " <-> " << cycles[cycle][nodeBIndex] << "\n";

	int currentDistance = DistanceToNeighbours(cycle, nodeAIndex) + DistanceToNeighbours(cycle, nodeBIndex);

	//std::cout << cycles[cycle][PrevNodeIndex(cycle, nodeAIndex)] << " -> " << cycles[cycle][nodeAIndex] << " -> " << cycles[cycle][NextNodeIndex(cycle, nodeAIndex)] << "\n";
	//std::cout << cycles[cycle][PrevNodeIndex(cycle, nodeBIndex)] << " -> " << cycles[cycle][nodeBIndex] << " -> " << cycles[cycle][NextNodeIndex(cycle, nodeBIndex)] << "\n";

	InternalNodeSwap(cycle, nodeAIndex, nodeBIndex);

	int distanceAfterSwap = DistanceToNeighbours(cycle, nodeAIndex) + DistanceToNeighbours(cycle, nodeBIndex);

	//std::cout << cycles[cycle][PrevNodeIndex(cycle, nodeAIndex)] << " -> " << cycles[cycle][nodeAIndex] << " -> " << cycles[cycle][NextNodeIndex(cycle, nodeAIndex)] << "\n";
	//std::cout << cycles[cycle][PrevNodeIndex(cycle, nodeBIndex)] << " -> " << cycles[cycle][nodeBIndex] << " -> " << cycles[cycle][NextNodeIndex(cycle, nodeBIndex)] << "\n";

	InternalNodeSwap(cycle, nodeAIndex, nodeBIndex);

	return currentDistance - distanceAfterSwap;
}

int LocalSearch::ExternalNodeSwapGain(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
{
	//std::cout << "Swap gain " << cycles[cycleA][nodeAIndex] << " <-> " << cycles[cycleB][nodeBIndex] << "\n";

	int currentDistance = DistanceToNeighbours(cycleA, nodeAIndex) + DistanceToNeighbours(cycleB, nodeBIndex);

	//std::cout << cycles[cycleA][PrevNodeIndex(cycleA, nodeAIndex)] << " -> " << cycles[cycleA][nodeAIndex] << " -> " << cycles[cycleA][NextNodeIndex(cycleA, nodeAIndex)] << "\n";
	//std::cout << cycles[cycleB][PrevNodeIndex(cycleB, nodeBIndex)] << " -> " << cycles[cycleB][nodeBIndex] << " -> " << cycles[cycleB][NextNodeIndex(cycleB, nodeBIndex)] << "\n";

	ExternalNodeSwap(cycleA, nodeAIndex, cycleB, nodeBIndex);

	int distanceAfterSwap = DistanceToNeighbours(cycleA, nodeAIndex) + DistanceToNeighbours(cycleB, nodeBIndex);

	//std::cout << cycles[cycleA][PrevNodeIndex(cycleA, nodeAIndex)] << " -> " << cycles[cycleA][nodeAIndex] << " -> " << cycles[cycleA][NextNodeIndex(cycleA, nodeAIndex)] << "\n";
	//std::cout << cycles[cycleB][PrevNodeIndex(cycleB, nodeBIndex)] << " -> " << cycles[cycleB][nodeBIndex] << " -> " << cycles[cycleB][NextNodeIndex(cycleB, nodeBIndex)] << "\n";

	ExternalNodeSwap(cycleA, nodeAIndex, cycleB, nodeBIndex);


	return currentDistance - distanceAfterSwap;
}

void LocalSearch::InternalNodeSwap(int cycle, int nodeAIndex, int nodeBIndex)
{
	int nodeA = cycles[cycle][nodeAIndex];
	cycles[cycle][nodeAIndex] = cycles[cycle][nodeBIndex];
	cycles[cycle][nodeBIndex] = nodeA;
}

void LocalSearch::ExternalNodeSwap(int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
{
	int nodeA = cycles[cycleA][nodeAIndex];
	cycles[cycleA][nodeAIndex] = cycles[cycleB][nodeBIndex];
	cycles[cycleB][nodeBIndex] = nodeA;
}

