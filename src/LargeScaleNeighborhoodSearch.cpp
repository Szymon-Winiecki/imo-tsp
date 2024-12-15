#include "../include/LargeScaleNeighborhoodSearch.h"

#include "../include/Perturbator.h"
#include "../include/Result.h"

#include <variant>
#include <chrono>
#include <iostream>

Result* LargeScaleNeighborhoodSearch::Solve()
{
    uint64_t executionStart = GetCurrentTime();

    int bestLength = GetCurrentRouteLength();
    while (GetCurrentTime() - executionStart < maxExecutionTime)
    {
		std::vector<std::vector<int>> lastCycle = cycles;
		perturbator->Perturbate(cycles);

        if (GetCurrentRouteLength() < bestLength)
        {
            bestLength = GetCurrentRouteLength();
        }
        else
        {
			cycles = lastCycle;
        }
    }

    return GetResult();
}

uint64_t LargeScaleNeighborhoodSearch::GetCurrentTime()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

