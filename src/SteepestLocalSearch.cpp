#include "../include/RegretSolver.h"

#include <list>
#include <vector>
#include <utility>
#include <limits>
#include <iterator>
#include <iostream>

#include "../include/SteepestLocalSearch.h"
#include "../include/LocalSearch.h"
#include "../include/Result.h"
#include "../include/Instance.h"

Result* SteepestLocalSearch::Solve()
{
	Result* result = new Result(instance, cycles.size());

	int gain = 0;
	int bestGain = 0;
	int cycleA = -1;
	int cycleB = -1;
	int nodeAIndex = -1;
	int nodeBIndex = -1;
	int type = 0;
	do
	{
		// swap nodes between cycles
		bestGain = 0;
		for (int i = 0; i < cycles.size(); ++i)
		{
			for (int node = 0; node < cycles[i].size(); ++node)
			{
				for (int j = 0; j < cycles.size(); ++j)
				{
					if (i == j) continue;
					for (int node2 = 0; node2 < cycles[j].size(); ++node2)
					{
						gain = ExternalNodeSwapGain(i, node, j, node2);
						if (gain > bestGain)
						{
							bestGain = gain;
							cycleA = i;
							cycleB = j;
							nodeAIndex = node;
							nodeBIndex = node2;
							type = 0;
						}
					}
				}
			}
		}

		for (int i = 0; i < cycles.size(); ++i)
		{
			for (int nodeA = 0; nodeA < cycles[i].size(); ++nodeA)
			{
				for (int nodeB = 0; nodeB < cycles[i].size(); ++nodeB)
				{
					if (nodeA == nodeB) continue;

					if (InternalMoveType == MoveType::InternalNodeSwap)
					{
						gain = InternalNodeSwapGain(i, nodeA, nodeB);
					}
					else if (InternalMoveType == MoveType::InternalEdgeSwap)
					{
						gain = InternalEdgeSwapGain(i, nodeA, nodeB);
					}

					if (gain > bestGain)
					{
						bestGain = gain;
						cycleA = i;
						nodeAIndex = nodeA;
						nodeBIndex = nodeB;
						type = 1;
					}
				}
			}
		}

		
		if (bestGain > 0)
		{
			if (type == 0)
				ExternalNodeSwap(cycleA, nodeAIndex, cycleB, nodeBIndex);
			else if (type == 1)
			{
				if (InternalMoveType == MoveType::InternalNodeSwap)
				{
					InternalNodeSwap(cycleA, nodeAIndex, nodeBIndex);
				}
				else if (InternalMoveType == MoveType::InternalEdgeSwap)
				{
					InternalEdgeSwap(cycleA, nodeAIndex, nodeBIndex);
				}

			}
		}
	} while (bestGain > 0);



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
