#include "../include/CachedSteepestLocalSearch.h"

#include "../include/NodeSwapMove.h"
#include "../include/EdgeSwapMove.h"
#include "../include/Result.h"
#include "../include/CyclesContext.h"

#include <forward_list>
#include <iostream>

Result* CachedSteepestLocalSearch::Solve()
{
	std::shared_ptr<CyclesContext> context = std::make_shared<CyclesContext>(instance, cycles, indexOfNode);

	ConstructInitialMoves();

	while (!movesQueue.empty())
	{
		std::forward_list<std::shared_ptr<Move>> movesToRestore;
		std::shared_ptr<Move> nextMove = nullptr;

		do
		{
			nextMove = movesQueue.top();
			movesQueue.pop();

			if (nextMove->IsApplicable())
			{
				break;
			}
			else if (!(nextMove->ShouldRemove()))
			{
				movesToRestore.push_front(nextMove);
			}

			
		} while (!movesQueue.empty());

		if (nextMove != nullptr && nextMove->IsApplicable())
		{
			nextMove->Apply();
		}
		else 
		{
			break;
		}

		for (int node : nextMove->GetAffectedNodes())
		{
			int cycle = context->NodeCycle(node);
			int nodeIndex = context->NodeIndex(node);

			for (int otherCycle = 0; otherCycle < cycles.size(); ++otherCycle)
			{
				if (cycle == otherCycle)
				{
					continue;
				}

				for (int otherNodeIndex = 0; otherNodeIndex < cycles[otherCycle].size(); ++otherNodeIndex)
				{
					std::shared_ptr<Move> move = std::make_shared<NodeSwapMove>(context, cycle, nodeIndex, otherCycle, otherNodeIndex);
					if (move->GetGain() > 0)
					{
						movesQueue.push(move);
					}
				}
			}
		}

		for (std::array<int, 2> edge : nextMove->GetNewEdges())
		{
			int cycle = context->NodeCycle(edge[0]);
			int edgeIndex = context->NodeIndex(edge[0]);

			for (int otherEdgeIndex = 0; otherEdgeIndex < cycles[cycle].size(); ++otherEdgeIndex)
			{
				if (edgeIndex == otherEdgeIndex)
				{
					continue;
				}

				std::shared_ptr<Move> move = std::make_shared<EdgeSwapMove>(context, edge[0], edge[1], context->NodeAt(cycle, otherEdgeIndex), context->NextNode(cycle, otherEdgeIndex));
				if (move->GetGain() > 0)
				{
					movesQueue.push(move);
				}

				std::shared_ptr<Move> moveReversed = std::make_shared<EdgeSwapMove>(context, edge[1], edge[0], context->NodeAt(cycle, otherEdgeIndex), context->NextNode(cycle, otherEdgeIndex));
				if (moveReversed->GetGain() > 0)
				{
					movesQueue.push(moveReversed);
				}
			}
		}
		

		while (!movesToRestore.empty())
		{
			movesQueue.push(movesToRestore.front());
			movesToRestore.pop_front();
		}

	}

	return GetResult();
}

void CachedSteepestLocalSearch::ConstructInitialMoves()
{
	std::shared_ptr<CyclesContext> context = std::make_shared<CyclesContext>(instance, cycles, indexOfNode);

	// EXTERNAL NODE MOVES
	for (int cycleA = 0; cycleA < cycles.size(); ++cycleA)
	{
		for (int cycleB = cycleA + 1; cycleB < cycles.size(); ++cycleB)
		{
			for (int nodeAIndex = 0; nodeAIndex < cycles[cycleA].size(); ++nodeAIndex)
			{
				for (int nodeBIndex = 0; nodeBIndex < cycles[cycleB].size(); ++nodeBIndex)
				{
					std::shared_ptr<Move> move = std::make_shared<NodeSwapMove>(context, cycleA, nodeAIndex, cycleB, nodeBIndex);
					if (move->GetGain() > 0)
					{
						movesQueue.push(move);
					}
					
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
				std::shared_ptr<Move> move = std::make_shared<EdgeSwapMove>(context, context->NodeAt(cycle, edgeAIndex), context->NextNode(cycle, edgeAIndex), context->NodeAt(cycle, edgeBIndex), context->NextNode(cycle, edgeBIndex));
				if (move->GetGain() > 0)
				{
					movesQueue.push(move);
				}

				std::shared_ptr<Move> moveReversed = std::make_shared<EdgeSwapMove>(context, context->NextNode(cycle, edgeAIndex), context->NodeAt(cycle, edgeAIndex), context->NodeAt(cycle, edgeBIndex), context->NextNode(cycle, edgeBIndex));
				if (moveReversed->GetGain() > 0)
				{
					movesQueue.push(moveReversed);
				}
			}
		}
	}
}
