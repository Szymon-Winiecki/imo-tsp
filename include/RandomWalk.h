#pragma once

#include <utility>
#include <vector>
#include <list>

#include "LocalSearch.h"

class Result;
class Instance;


class RandomWalk : public LocalSearch
{
public:
	RandomWalk(std::vector<std::vector<int>> initialState, Instance* instance) : RandomWalk(initialState, instance, 100) {}

	RandomWalk(std::vector<std::vector<int>> initialState, Instance* instance, uint64_t maxExecutionTime) : LocalSearch(initialState, instance), maxExecutionTime{ maxExecutionTime } {}

	Result* Solve();

protected:
	uint64_t GetCurrentTime();

	uint64_t maxExecutionTime;
};