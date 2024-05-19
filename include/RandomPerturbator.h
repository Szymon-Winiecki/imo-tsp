#pragma once

#include "Perturbator.h"

class RandomPerturbator : public Perturbator
{
public:
	RandomPerturbator(int numChanges) : numChanges{ numChanges } {}

	virtual void Perturbate(std::vector<std::vector<int>>& cycles);

protected:

	void SwapNodes(std::vector<std::vector<int>>& cycles, int cycleA, int nodeAIndex, int cycleB, int nodeBIndex);
	void SwapEdges(std::vector<std::vector<int>>& cycles, int cycle, int edgeAIndex, int edgeBIndex);

	int numChanges;
};