#include "../include/NearestNeighborSolver.h"

#include <list>
#include <vector>
#include <utility>
#include <limits>
#include <iterator>

#include "../include/Result.h"
#include "../include/Instance.h"

Result* NearestNeighborSolver::Solve(int routesNumber)
{
	if (routesNumber > instance->Size()) {
		return new Result(instance);
	}

	Result* result = new Result(instance);

	int nodesUsedNumber = routesNumber;
	std::vector<bool> nodesUsed(instance->Size(), false);

	std::vector<std::list<int>> routes(routesNumber);

	int startNode = GetRandomNode();
	for (int i = 0; i < routes.size(); ++i) 
	{
		routes[i].push_front(startNode);
		nodesUsed[startNode] = true;
		if (++startNode >= instance->Size()) 
		{
			startNode = 0;
		}
	}


	int currentRoute = 0;
	while (nodesUsedNumber < instance->Size())
	{
		std::pair<int, int> bestInsertion = FindBestInsertion(routes[currentRoute], nodesUsed);
		int insertAfter = bestInsertion.first;
		int insertNode = bestInsertion.second;

		auto insertIterator = std::next(routes[currentRoute].begin(), insertAfter + 1);
		routes[currentRoute].insert(insertIterator, insertNode);
		++nodesUsedNumber;
		nodesUsed[insertNode] = true;

		if (++currentRoute >= routesNumber) 
		{
			currentRoute = 0;
		}
	}

	for (int i = 0; i < routes.size(); ++i) 
	{
		int lastNode = -1;

		for (auto node : routes[i])
		{
			if(lastNode != -1)
			{
				result->AddEdge(i, lastNode, node);
			}
			lastNode = node;
		}
	}

	return result;
}

std::pair<int, int> NearestNeighborSolver::FindBestInsertion(const std::list<int>& route, const std::vector<bool>& nodeUsed) const
{
	int bestNode = 0;
	int bestSegment = 0;
	int bestLengthIncrease = std::numeric_limits<int>::max();

	int currentSegment = 0;
	for (auto segment = route.begin(); segment != route.end(); segment++) {
		int segmentStart = *segment;
		segment++;
		
		int segmentEnd = -1;
		if(segment != route.end())
		{
			segmentEnd = *segment;
		}
		segment--;

		for (int i = 0; i < nodeUsed.size(); ++i) {
			if (nodeUsed[i]) continue;
			int lengthIncrease = 0;

			if (segmentEnd == -1)	// appending at the end of the route
			{
				lengthIncrease = instance->Distance(segmentStart, i);
			}
			else // inserting somewhere in the middle of the route
			{
				lengthIncrease = instance->Distance(segmentStart, i) + instance->Distance(i, segmentEnd) - instance->Distance(segmentStart, segmentEnd);
			}
			

			if (lengthIncrease < bestLengthIncrease) {
				bestLengthIncrease = lengthIncrease;
				bestNode = i;
				bestSegment = currentSegment;
			}
		}

		++currentSegment;
	}

	return { bestSegment, bestNode };
}