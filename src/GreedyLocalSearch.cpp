#include "../include/RegretSolver.h"

#include <list>
#include <vector>
#include <utility>
#include <limits>
#include <iterator>
#include <iostream>
#include <time.h> 
#include <cstdlib>
#include <ctime>

#include "../include/GreedyLocalSearch.h"
#include "../include/LocalSearch.h"
#include "../include/Result.h"
#include "../include/Instance.h"

Result* GreedyLocalSearch::Solve()
{
	Result* result = new Result(instance, cycles.size());
	int counter = 0;
	int gain = 0;
	int type = 0;
	int change = 0;
	int randNeigh = 0;
	int randNode = 0;
	int randCounter = 2;
	int randCycle = 0;
	int randNodeB = 0;

	do
	{
		//Zamiana wierzcho³ków miêdzy cyklami
		change = 0;

		if (randCounter == 2)
		{
			randCycle = rand() % cycles.size(); // random cycle
			randNode = rand() % instance->Size() / cycles.size(); // begining node
			randNeigh = rand() % 2; // neighborhood type
			randNodeB = rand() % instance->Size() / cycles.size(); // node to swap
			change = 1;
		}
		else
		{
			randCycle = 0;
			randNode = 0;
			randNodeB = 0;
			randNeigh = -1;
		}
		randCounter--;

		if (randNeigh == 0 || randCounter == 0)
		{
			for (int i = randCycle; i < cycles.size(); ++i)
			{
				for (int node = randNode; node < cycles[i].size(); ++node)
				{
					for (int j = 0; j < cycles.size(); ++j)
					{
						if (i == j) continue;
						for (int node2 = randNodeB; node2 < cycles[j].size(); ++node2)
						{
							gain = ExternalNodeSwapGain(i, node, j, node2);

							if (gain > 0)
							{
								ExternalNodeSwap(i, node, j, node2);
								change = 1;
								randCounter = 2;
							}
						}
					}
				}
			}
		}
		if (randNeigh == 1 || randCounter == 0)
		{
			for (int i = randCycle; i < cycles.size(); ++i)
			{
				for (int nodeA = randNode; nodeA < cycles[i].size(); ++nodeA)
				{
					for (int nodeB = randNodeB; nodeB < cycles[i].size(); ++nodeB)
					{
						if (nodeA == nodeB) continue;

						if (internalMoveType == MoveType::InternalNodeSwap)
						{
							gain = InternalNodeSwapGain(i, nodeA, nodeB);
						}
						else if (internalMoveType == MoveType::InternalEdgeSwap)
						{
							gain = InternalEdgeSwapGain(i, nodeA, nodeB);
						}
						if (gain > 0)
						{
							randCounter = 2;
							if (internalMoveType == MoveType::InternalNodeSwap)
							{
								InternalNodeSwap(i, nodeA, nodeB);
							}
							else if (internalMoveType == MoveType::InternalEdgeSwap)
							{
								InternalEdgeSwap(i, nodeA, nodeB);
							}
							change = 1;
						}
					}
				}
			}
		}
		counter++;
	}while(change > 0 && counter < 5000 && randCounter > 0);
	


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

std::pair<int, int> GreedyLocalSearch::FindBestChange(const std::list<int>& route, const std::vector<bool>& nodeUsed) const
{
	return { 0, 0 };
}