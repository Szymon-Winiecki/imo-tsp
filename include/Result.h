#pragma once

#include <vector>
#include <array>

class Instance;

typedef std::vector<std::array<int, 2>> EdgeList_t;

class Result
{
public:
	Result(Instance* instance, int routesCount = 2);

	void AddEdge(int route, int start, int end);

	void Plot();
private:
	Instance* instance;
	std::vector<EdgeList_t> routes;
};