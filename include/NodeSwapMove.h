#pragma once

#include "Move.h"

#include <array>
#include <memory>

class NodeSwapMove : public Move
{
public:
	NodeSwapMove(std::shared_ptr<CyclesContext> context, int cycleA, int nodeAIndex, int cycleB, int nodeBIndex);

	bool IsApplicable() const;
	bool ShouldRemove() const;
	int Apply();
	std::vector<int> GetAffectedNodes();
	std::vector < std::array<int, 2>> GetNewEdges();

protected:
	int nodeA, nodeB;

	std::array<int, 2> nodeANeigh;
	std::array<int, 2> nodeBNeigh;
};