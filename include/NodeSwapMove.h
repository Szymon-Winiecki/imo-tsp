#pragma once

#include "Move.h"

#include <array>

class NodeSwapMove : public Move
{
public:
	NodeSwapMove(CyclesContext* context, int cycleA, int nodeAIndex, int cycleB, int nodeBIndex);

	bool IsApplicable() const;
	int Apply();
protected:
	int cycleA, nodeAIndex, cycleB, nodeBIndex;

	std::array<int, 3> nodeANeigh;	// nodeA neighbourhood (actuall names of nodes, not just indices), where nodeANeigh[1] is the nodeA itself
	std::array<int, 3> nodeBNeigh;
};