#pragma once

#include "Move.h"

#include <array>

class EdgeSwapMove : public Move
{
public:
	EdgeSwapMove(CyclesContext* context, int cycle, int edgeAIndex, int edgeBIndex);

	bool IsApplicable() const;
	int Apply();
protected:
	int cycle, edgeAIndex, edgeBIndex;

	std::array<int, 2> edgeA;	// nodeA neighbourhood (actuall names of nodes, not just indices), where nodeANeigh[1] is the nodeA itself
	std::array<int, 3> edgeB;
};