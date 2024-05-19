#pragma once

#include "Perturbator.h"

#include <list>

class Solver;

class DestroyRepairPerturbator : public Perturbator
{
public:
	DestroyRepairPerturbator(int numChanges, Solver* solver)
		: numChanges{ numChanges }, 
		solver{ solver } {}

	virtual void Perturbate(std::vector<std::vector<int>>& cycles);

protected:

	std::list<int> Destroy(std::vector<std::vector<int>>& cycles, int cycle, int cutStart, int cutLength);

	int numChanges;
	Solver* solver;
};