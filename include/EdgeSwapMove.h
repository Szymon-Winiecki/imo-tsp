#pragma once

#include "Move.h"

#include <array>
#include <memory>

class EdgeSwapMove : public Move
{
public:
	EdgeSwapMove(std::shared_ptr<CyclesContext> context, int edgeAStart, int edgeAEnd, int edgeBStart, int edgeBEnd);

	bool IsApplicable() const;
	bool ShouldRemove() const;
	int Apply();
	std::vector<int> GetAffectedNodes();
	std::vector < std::array<int, 2>> GetNewEdges();

protected:
	std::array<int, 2> edgeA;
	std::array<int, 2> edgeB;
};