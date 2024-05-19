#pragma once

#include <utility>
#include <vector>
#include <list>
#include <tuple>

#include "LocalSearch.h"

class Result;
class Instance;
class Perturbator;


template <class T, class... Params>
class IteratedLocalSearch : public LocalSearch
{
public:
	IteratedLocalSearch(std::vector<std::vector<int>> initialState, Instance* instance, Perturbator* perturbator, uint64_t maxExecutionTime, Params&&... parameters)
		: LocalSearch(initialState, instance), 
		perturbator{ perturbator }, 
		maxExecutionTime{ maxExecutionTime }
	{
		static_assert(std::is_base_of<LocalSearch, T>::value, "T must inherit from LocalSearch");

		params = std::make_tuple(std::move(parameters)...);
	}

	Result* Solve();

protected:
	uint64_t GetCurrentTime();

	Perturbator* perturbator;
	std::tuple<Params...> params;

	uint64_t maxExecutionTime;
};