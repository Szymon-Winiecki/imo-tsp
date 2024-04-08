#include "../include/RandomWalk.h"
#include "../include/Instance.h"
#include "../include/Result.h"

#include <chrono>

Result* RandomWalk::Solve()
{
	uint64_t executionStart = GetCurrentTime();

	Result* result = new Result(instance, cycles.size());

	std::vector<std::vector<int>> bestResult = cycles;
	int bestResultCost = 0;

	for(int c = 0; c < cycles.size(); ++c)
	{
		for (int e = 0; e < cycles[c].size(); ++e)
		{
			bestResultCost += instance->Distance(cycles[c][e], cycles[c][NextNodeIndex(c, e)]);
		}
	}

	int currentCost = bestResultCost;

	while (GetCurrentTime() - executionStart < maxExecutionTime)
	{
		MoveType moveType = static_cast<MoveType>(rand() % 3);

		if (moveType == MoveType::ExternalNodeSwap)
		{
			int cycleA = rand() % cycles.size();
			int nodeAIndex = rand() % cycles[cycleA].size();
			int cycleB = rand() % cycles.size();
			int nodeBIndex = rand() % cycles[cycleB].size();

			if (cycleA == cycleB) 
			{
				cycleB = cycleA > 0 ? (cycleA - 1) : (cycleA + 1);
				
			}

			currentCost -= ExternalNodeSwapGain(cycleA, nodeAIndex, cycleB, nodeBIndex);
			ExternalNodeSwap(cycleA, nodeAIndex, cycleB, nodeBIndex);
		}
		else if (moveType == MoveType::InternalNodeSwap)
		{
			int cycle = rand() % cycles.size();
			int nodeAIndex = rand() % cycles[cycle].size();
			int nodeBIndex = rand() % cycles[cycle].size();

			if (nodeAIndex == nodeAIndex)
			{
				continue;
			}

			currentCost -= InternalNodeSwapGain(cycle, nodeAIndex, nodeBIndex);
			InternalNodeSwap(cycle, nodeAIndex, nodeBIndex);
		}
		else if (moveType == MoveType::InternalEdgeSwap)
		{
			int cycle = rand() % cycles.size();
			int edgeAIndex = rand() % cycles[cycle].size();
			int edgeBIndex = rand() % cycles[cycle].size();

			if (edgeAIndex == edgeBIndex)
			{
				continue;
			}

			currentCost -= InternalEdgeSwapGain(cycle, edgeAIndex, edgeBIndex);
			InternalEdgeSwap(cycle, edgeAIndex, edgeBIndex);
		}

		if (currentCost < bestResultCost)
		{
			bestResultCost = currentCost;
			bestResult = cycles;
		}
	}

	for (int i = 0; i < bestResult.size(); ++i)
	{
		int lastNode = -1;

		for (auto node : bestResult[i])
		{
			if (lastNode != -1)
			{
				result->AddEdge(i, lastNode, node);
			}
			lastNode = node;
		}
		result->AddEdge(i, lastNode, bestResult[i].front());
	}

	return result;
}

uint64_t RandomWalk::GetCurrentTime()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
