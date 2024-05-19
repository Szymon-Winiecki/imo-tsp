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
		//std::cout << "Best length: " << bestLength << std::endl;
        T localSearch = T(cycles, instance, std::get<Params>(params)...);
		perturbator->Perturbate(localSearch.GetCycles());
        Result* localSearchResult = localSearch.Solve();

        //std::cout << "Current length: " << localSearchResult->getRouteLength() << std::endl;

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
template class IteratedLocalSearch<SteepestLocalSearch, int>;
template class IteratedLocalSearch<GreedyLocalSearch, int>;

