#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>

class Instance;
class Result;

class Solver 
{
public:
	Solver(Instance* instance) : instance { instance } { }

	void SetInstance(Instance* instance) 
	{
		this->instance = instance;
	}

	Instance* GetInstance() const 
	{
		return instance;
	}

	virtual Result* Solve(int routes = 2) = 0;
	virtual void Solve(std::vector<std::list<int>>& routes) = 0;

protected:

	int RandomInt(int min, int max) const;
	int GetRandomNode() const;
	int GetTheFarthestNode(const std::vector<int>& fromNodes);
	int CalcSumDistanceToNodes(int node, const std::vector<int>& otherNodes);

	Instance* instance;
};