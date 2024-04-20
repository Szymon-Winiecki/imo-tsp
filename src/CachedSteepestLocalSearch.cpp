#include "../include/CachedSteepestLocalSearch.h"

#include "../include/NodeSwapMove.h"
#include "../include/EdgeSwapMove.h"
#include "../include/Result.h"
#include "../include/CyclesContext.h"

Result* CachedSteepestLocalSearch::Solve()
{
	Result* result = new Result(instance, cycles.size());

	ConstructInitialMoves();


	return nullptr;
}

void CachedSteepestLocalSearch::ConstructInitialMoves()
{
	CyclesContext* context = new CyclesContext(instance, cycles);

	// INTERNAL NODE MOVES
	for (int cycle = 0; cycle < cycles.size(); ++cycle) 
	{
		for (int nodeAIndex = 0; nodeAIndex < cycles[cycle].size(); ++nodeAIndex)
		{
			for (int nodeBIndex = nodeAIndex + 1; nodeBIndex < cycles[cycle].size(); ++nodeBIndex)
			{
				movesQueue.push(new NodeSwapMove(context, cycle, nodeAIndex, cycle, nodeBIndex));
			}
		}
	}

	// EXTERNAL NODE MOVES
	for (int cycleA = 0; cycleA < cycles.size(); ++cycleA)
	{
		for (int cycleB = cycleA + 1; cycleB < cycles.size(); ++cycleB)
		{
			for (int nodeAIndex = 0; nodeAIndex < cycles[cycleA].size(); ++nodeAIndex)
			{
				for (int nodeBIndex = 0; nodeBIndex < cycles[cycleB].size(); ++nodeBIndex)
				{
					movesQueue.push(new NodeSwapMove(context, cycleA, nodeAIndex, cycleB, nodeBIndex));
				}
			}
		}
	}

	// INTERNAL EDGE MOVE
	for (int cycle = 0; cycle < cycles.size(); ++cycle)
	{
		for (int edgeAIndex = 0; edgeAIndex < cycles[cycle].size(); ++edgeAIndex)
		{
			for (int edgeBIndex = edgeAIndex + 1; edgeBIndex < cycles[cycle].size(); ++edgeBIndex)
			{
				movesQueue.push(new EdgeSwapMove(context, cycle, edgeAIndex, edgeBIndex));
			}
		}
	}

	// TODO: swap for inversed edges
}
