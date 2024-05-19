#pragma once

#include <utility>
#include <vector>
#include <list>

#include "Solver.h"

class Result;

class GreedyCycleSolver : public Solver
{
public:
	GreedyCycleSolver(Instance* instance) : Solver(instance) {}

	Result* Solve(int routes = 2) override;
	void Solve(std::vector<std::list<int>>& routes) override;

private:
	std::pair<int, int> FindBestInsertion(const std::list<int>& route, const std::vector<bool>& usedNodes) const;

};