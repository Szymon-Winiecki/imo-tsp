#include "../include/NodeSwapMove.h"

#include "../include/CyclesContext.h"

NodeSwapMove::NodeSwapMove(CyclesContext* context, int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
	: Move(context)
{
	nodeA = context->NodeAt(cycleA, nodeAIndex);
	nodeB = context->NodeAt(cycleB, nodeBIndex);

	gain = context->NodeSwapGain(cycleA, nodeAIndex, cycleB, nodeBIndex);

	nodeANeigh[0] = context->PrevNode(cycleA, nodeAIndex);
	nodeANeigh[1] = context->NextNode(cycleA, nodeAIndex);

	nodeBNeigh[0] = context->PrevNode(cycleB, nodeBIndex);
	nodeBNeigh[1] = context->NextNode(cycleB, nodeBIndex);
};

bool NodeSwapMove::IsApplicable() const
{
	if (
		context->IsNeighbourhood(nodeA, nodeANeigh[0], nodeANeigh[1]) &&
		context->IsNeighbourhood(nodeB, nodeBNeigh[0], nodeBNeigh[1])
		)
	{
		return true;
	}
	else {
		return false;
	}
	
}

bool NodeSwapMove::ShouldRemove() const
{
	return !IsApplicable();
}

int NodeSwapMove::Apply()
{
	context->NodeSwap(nodeA, nodeB);
	return gain;
}

std::vector<int> NodeSwapMove::GetAffectedNodes()
{
	return { nodeA, nodeANeigh[0], nodeANeigh[1], nodeB, nodeBNeigh[0], nodeBNeigh[1] };
}

std::vector<std::array<int, 2>> NodeSwapMove::GetNewEdges()
{
	return { {nodeANeigh[0], nodeB}, {nodeB, nodeANeigh[1]}, {nodeBNeigh[0], nodeA}, {nodeA, nodeBNeigh[1]} };
}
