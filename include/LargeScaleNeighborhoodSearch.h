#pragma once

#include <utility>
#include <vector>
#include <list>
#include <tuple>

#include "LocalSearch.h"

class Result;
class Instance;
class Perturbator;


class LargeScaleNeighborhoodSearch : public LocalSearch
{
public:
	LargeScaleNeighborhoodSearch(std::vector<std::vector<int>> initialState, Instance* instance, Perturbator* perturbator, uint64_t maxExecutionTime)
		: LocalSearch(initialState, instance), 
		perturbator{ perturbator }, 
		maxExecutionTime{ maxExecutionTime }
	{	}

	Result* Solve();

protected:
	uint64_t GetCurrentTime();

	Perturbator* perturbator;

	uint64_t maxExecutionTime;
};