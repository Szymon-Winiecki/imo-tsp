#include "../include/Solver.h"

#include "../include/Instance.h"

#include <algorithm>

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
