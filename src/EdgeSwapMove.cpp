#include "../include/EdgeSwapMove.h"

#include "../include/CyclesContext.h"

EdgeSwapMove::EdgeSwapMove(CyclesContext* context, int cycle, int edgeAIndex, int edgeBIndex)
	: Move(context),
	cycle{ cycle },
	edgeAIndex{ edgeAIndex },
	edgeBIndex{ edgeBIndex }
{
	if (this->edgeAIndex > this->edgeBIndex)
	{
		std::swap(this->edgeAIndex, this->edgeBIndex);
	}

	gain = context->EdgeSwapGain(this->cycle, this->edgeAIndex, this->edgeBIndex);

	edgeA[0] = context->NodeAt(this->cycle, this->edgeAIndex);
	edgeA[1] = context->NextNodeIndex(this->cycle, this->edgeAIndex);

	edgeB[0] = context->PrevNodeIndex(this->cycle, this->edgeBIndex);
	edgeB[1] = context->NodeAt(this->cycle, this->edgeBIndex);
};

bool EdgeSwapMove::IsApplicable() const
{
	if (
		edgeA[0] == context->NodeAt(this->cycle, this->edgeAIndex) &&
		edgeA[1] == context->NextNodeIndex(this->cycle, this->edgeAIndex) &&
		edgeB[0] == context->PrevNodeIndex(this->cycle, this->edgeBIndex) &&
		edgeB[1] == context->NodeAt(this->cycle, this->edgeBIndex)
		)
	{
		return true;
	}
	else {
		return false;
	}
	
}

int EdgeSwapMove::Apply()
{
	context->EdgeSwap(cycle, edgeAIndex, edgeBIndex);
	return gain;
}
