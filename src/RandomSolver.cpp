#include "../include/RandomSolver.h"

#include <list>
#include <vector>
#include <utility>
#include <limits>
#include <iterator>
#include <iostream>
#include <stdlib.h>  

#include "../include/Result.h"
#include "../include/Instance.h"
#include <time.h> 

Result* RandomSolver::Solve(int routesNumber)
{
	if (routesNumber > instance->Size()) {	// too much routes to construct with given instance (more routes than nodes)
		return new Result(instance);
	}
	srand(time(NULL));
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
		std::pair<int, int> bestInsertion = FindBestInsertion(routes[currentRoute], nodesUsed, nodesUsedNumber);
		int insertAfter = bestInsertion.first;
		int insertNode = bestInsertion.second;
		// insert node
		auto insertIterator = std::next(routes[currentRoute].begin(), insertAfter + 1);
		routes[currentRoute].insert(insertIterator, insertNode);
		++nodesUsedNumber;
		nodesUsed[insertNode] = true;
		//std::cout << nodesUsedNumber << std::endl;
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

std::pair<int, int> RandomSolver::FindBestInsertion(const std::list<int>& route, const std::vector<bool>& nodeUsed, int nodesUsedNumber) const
{
	int random  = rand() % (nodeUsed.size() - nodesUsedNumber);
	//std::cout << random << " -- " << nodeUsed.size() - nodesUsedNumber << std::endl;
	int j = 0;
	for (int i = 0; i < nodeUsed.size(); i++)
	{
		if (nodeUsed[i]) continue;

		if (random == j)
		{
			return { rand() % route.size(), i };
		}
		j++;

	}

}