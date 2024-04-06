#pragma once

#include <utility>
#include <vector>
#include <list>

#include "Solver.h"

class Result;

class RegretSolver : Solver
{
public:
	RegretSolver(Instance* instance) : Solver(instance) {}

	RegretSolver(Instance* instance, unsigned int seed) : Solver(instance, seed) {}

	Result* Solve(int routes = 2) override;

private:
	std::pair<int, int> FindBestInsertion(const std::list<int>& route, const std::vector<bool>& usedNodes) const;

};