#include "../include/EdgeSwapMove.h"

#include "../include/CyclesContext.h"

EdgeSwapMove::EdgeSwapMove(std::shared_ptr<CyclesContext> context, int edgeAStart, int edgeAEnd, int edgeBStart, int edgeBEnd)
	: Move(context)
{
	gain = context->EdgeSwapGain(edgeAStart, edgeAEnd, edgeBStart, edgeBEnd);

	edgeA[0] = edgeAStart;
	edgeA[1] = edgeAEnd;

	edgeB[0] = edgeBStart;
	edgeB[1] = edgeBEnd;
};

bool EdgeSwapMove::IsApplicable() const
{
	return (context->IsEdge(edgeA[0], edgeA[1]) && context->IsEdge(edgeB[0], edgeB[1])) || (context->IsEdge(edgeA[1], edgeA[0]) && context->IsEdge(edgeB[1], edgeB[0]));
}

bool EdgeSwapMove::ShouldRemove() const
{
	return !(context->IsEdgeOrReversedEdge(edgeA[0], edgeA[1]) && context->IsEdgeOrReversedEdge(edgeB[0], edgeB[1]));
}

int EdgeSwapMove::Apply()
{
	if (context->IsEdge(edgeA[0], edgeA[1]))
	{
		context->EdgeSwap(edgeA[0], edgeB[0]);
	}
	else
	{
		context->EdgeSwap(edgeA[1], edgeB[1]);
	}
	
	return gain;
}

std::vector<int> EdgeSwapMove::GetAffectedNodes()
{
	return {edgeA[0], edgeA[1], edgeB[0], edgeB[1]};
}

std::vector<std::array<int, 2>> EdgeSwapMove::GetNewEdges()
{
	return { {edgeA[0], edgeB[0]}, {edgeA[1], edgeB[1]} };
}
