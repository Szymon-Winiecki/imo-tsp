#include "../include/IteratedLocalSearch.h"

#include "../include/CachedSteepestLocalSearch.h"
#include "../include/SteepestLocalSearch.h"
#include "../include/GreedyLocalSearch.h"
#include "../include/Perturbator.h"
#include "../include/Result.h"

#include <variant>
#include <chrono>
#include <iostream>

template <class T, class... Params>
Result* IteratedLocalSearch<T, Params...>::Solve()
{
    uint64_t executionStart = GetCurrentTime();

    int bestLength = GetCurrentRouteLength();
    while (GetCurrentTime() - executionStart < maxExecutionTime)
    {
        T localSearch = T(cycles, instance, std::get<Params>(params)...);
		perturbator->Perturbate(localSearch.GetCycles());
        Result* localSearchResult = localSearch.Solve();

        if (localSearchResult->getRouteLength() < bestLength)
        {
            cycles = localSearchResult->GetCycles();
            bestLength = localSearchResult->getRouteLength();
        }

		delete localSearchResult;
    }

    return GetResult();
}

template <class T, class... Params>
uint64_t IteratedLocalSearch<T, Params...>::GetCurrentTime()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

template class IteratedLocalSearch<CachedSteepestLocalSearch>;
template class IteratedLocalSearch<SteepestLocalSearch>;
template class IteratedLocalSearch<SteepestLocalSearch, MoveType>;
template class IteratedLocalSearch<GreedyLocalSearch, MoveType>;

