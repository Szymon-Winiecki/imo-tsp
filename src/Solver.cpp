#include "../include/Solver.h"

#include "../include/Instance.h"
#include "../include/Result.h"

#include <algorithm>
#include <chrono>

int Solver::RandomInt(int min, int max) const
{
	return min + (rand() % (max - min));
}

int Solver::GetRandomNode() const
{
	return RandomInt(0, instance->Size());
}

int Solver::GetTheFarthestNode(const std::vector<int>& fromNodes)
{
	int theFarthestNode = 0;
	int maxDistance = 0;

	for (int i = 0; i < instance->Size(); ++i) {

		if (std::find(fromNodes.begin(), fromNodes.end(), i) != fromNodes.end())	// don't choose node already in fromNodes
		{
			continue;
		}

		int distance = CalcSumDistanceToNodes(i, fromNodes);
		if (distance > maxDistance) 
		{
			maxDistance = distance;
			theFarthestNode = i;
		}

	}

	return theFarthestNode;
}

int Solver::CalcSumDistanceToNodes(int node, const std::vector<int>& otherNodes)
{
	int distance = 0;

	for (auto otherNode : otherNodes)
	{
		distance += instance->Distance(node, otherNode);
	}

	return distance;
}

Result* Solver::GetResult(std::vector<std::list<int>>& cycles) const
{
	Result* result = new Result(instance, cycles.size());

	// add all edges of constructed cycles to the result object
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

uint64_t Solver::GetCurrentTime()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
