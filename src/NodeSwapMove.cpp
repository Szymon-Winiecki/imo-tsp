#include "../include/NodeSwapMove.h"

#include "../include/CyclesContext.h"

NodeSwapMove::NodeSwapMove(CyclesContext* context, int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
	: Move(context),
	cycleA{ cycleA },
	nodeAIndex{ nodeAIndex },
	cycleB{ cycleB },
	nodeBIndex{ nodeBIndex }
{
	gain = context->NodeSwapGain(cycleA, nodeAIndex, cycleB, nodeBIndex);

	nodeANeigh[0] = context->PrevNode(cycleA, nodeAIndex);
	nodeANeigh[1] = context->NodeAt(cycleA, nodeAIndex);
	nodeANeigh[2] = context->NextNode(cycleA, nodeAIndex);

	nodeBNeigh[0] = context->PrevNode(cycleB, nodeBIndex);
	nodeBNeigh[1] = context->NodeAt(cycleB, nodeBIndex);
	nodeBNeigh[2] = context->NextNode(cycleB, nodeBIndex);
};

bool NodeSwapMove::IsApplicable() const
{
	if (
		nodeANeigh[0] == context->PrevNode(cycleA, nodeAIndex) &&
		nodeANeigh[1] == context->NodeAt(cycleA, nodeAIndex) &&
		nodeANeigh[2] == context->NextNode(cycleA, nodeAIndex) &&
		nodeBNeigh[0] == context->PrevNode(cycleB, nodeBIndex) &&
		nodeBNeigh[1] == context->NodeAt(cycleB, nodeBIndex) &&
		nodeBNeigh[2] == context->NextNode(cycleB, nodeBIndex)
		)
	{
		return true;
	}
	else {
		return false;
	}
	
}

int NodeSwapMove::Apply()
{
	context->NodeSwap(cycleA, nodeAIndex, cycleB, nodeBIndex);
	return gain;
}
