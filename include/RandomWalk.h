#pragma once

#include <utility>
#include <vector>
#include <list>

#include "LocalSearch.h"

class Result;
class Instance;


class RandomWalk : LocalSearch
{
public:
	RandomWalk(std::vector<std::vector<int>> initialState, Instance* instance, uint64_t maxExecutionTime) : RandomWalk(initialState, instance, maxExecutionTime, (unsigned int)time(NULL)) {}

	RandomWalk(std::vector<std::vector<int>> initialState, Instance* instance, uint64_t maxExecutionTime, unsigned int seed) : LocalSearch(initialState, instance, 0, seed), maxExecutionTime{ maxExecutionTime } {}

	Result* Solve();

protected:
	uint64_t GetCurrentTime();

	uint64_t maxExecutionTime;
};