#include "../include/RegretSolver.h"

#include <list>
#include <vector>
#include <utility>
#include <limits>
#include <iterator>
#include <iostream>

#include "../include/Result.h"
#include "../include/Instance.h"

Result* RegretSolver::Solve(int routesNumber)
{
	if (routesNumber > instance->Size()) {	// too much routes to construct with given instance (more routes than nodes)
		return new Result(instance);
	}

	Result* result = new Result(instance, routesNumber);

	int nodesUsedNumber = routesNumber;
	std::vector<bool> nodesUsed(instance->Size(), false);	// if node of index x is already included in one of the paths nodesUsed[x] = true, otherwise nodesUsed[x] = false

	std::vector<std::list<int>> routes(routesNumber);	// array of routes; route is a list of nodes indices in the order they are connected; also, it is assumed that last node is connected with first, to close the cycle

	// choosing fisrst node in every path
	std::vector<int> startNodes(0);
	startNodes.push_back(GetRandomNode());	// start node of the first route is choosed randomly
	//std::cout<<startNodes[0]<<"---!---" <<std::endl;
	for (int i = 0; i < routes.size(); ++i)
	{
		routes[i].push_front(startNodes[i]);
		nodesUsed[startNodes[i]] = true;

		startNodes.push_back(GetTheFarthestNode(startNodes));	// next routes starts with the node that is the farthest one form all previous routes start nodes
	}

	// iterate over all contructed cycles and add nodes until all nodes are used
	int currentRoute = 0;
	while (nodesUsedNumber < instance->Size())
	{
		// find which node and where should be inserted
		std::pair<int, int> bestInsertion = FindBestInsertion(routes[currentRoute], nodesUsed);
		int insertAfter = bestInsertion.first;
		int insertNode = bestInsertion.second;
		// insert node
		auto insertIterator = std::next(routes[currentRoute].begin(), insertAfter + 1);
		routes[currentRoute].insert(insertIterator, insertNode);
		++nodesUsedNumber;
		nodesUsed[insertNode] = true;

		if (++currentRoute >= routesNumber)
		{
			currentRoute = 0;
		}
	}

	// add all edges of constructed cycles to the result object
	for (int i = 0; i < routes.size(); ++i)
	{
		int lastNode = -1;

		for (auto node : routes[i])
		{
			if (lastNode != -1)
			{
				result->AddEdge(i, lastNode, node);
			}
			lastNode = node;
		}
		result->AddEdge(i, lastNode, routes[i].front());
	}

	return result;
}

std::pair<int, int> RegretSolver::FindBestInsertion(const std::list<int>& route, const std::vector<bool>& nodeUsed) const
{
	int bestNode = 0;
	int bestSegment = 0;
	int currBestSegment = 0;
	int regret = 0;
	int bestRegret = 0;
	std::pair<int, int> lengthIncreases = { std::numeric_limits<int>::max(),std::numeric_limits<int>::max() };

	for (int i = 0; i < nodeUsed.size(); ++i)
	{
		if (nodeUsed[i]) continue;

		int currentSegment = 0;
		for (auto segment = route.begin(); segment != route.end(); segment++)
		{
			int segmentStart = *segment;
			segment++;

			// edge form segmentStart node to segmentEnd node
			int segmentEnd = -1;
			if (segment != route.end())
			{
				segmentEnd = *segment;
			}
			else
			{
				segmentEnd = route.front();
			}
			segment--;

			int lengthIncrease = instance->Distance(segmentStart, i) + instance->Distance(i, segmentEnd) - instance->Distance(segmentStart, segmentEnd);
			//std::cout<< lengthIncrease << std::endl;
			if (lengthIncrease < lengthIncreases.first)
			{
				lengthIncreases.second = lengthIncreases.first;
				lengthIncreases.first = lengthIncrease;
				currBestSegment = currentSegment;
			}
			else if (lengthIncrease < lengthIncreases.second)
			{
				lengthIncreases.second = lengthIncrease;
			}
			++currentSegment; 
		}
		//std::cout <<lengthIncreases.first<<"---"<<lengthIncreases.second<<std::endl;
		regret = lengthIncreases.first - lengthIncreases.second;
		//std::cout<< regret;
		lengthIncreases = { std::numeric_limits<int>::max(),std::numeric_limits<int>::max() };
		//std::cout<< regret << "---"<<bestRegret << std::endl;
		if (bestRegret > regret)
		{
			bestRegret = regret;
			bestNode = i;
			bestSegment = currBestSegment;
		}
	}
	//std::cout << bestNode << "---" << bestSegment << std::endl;
	return { bestSegment, bestNode };
}