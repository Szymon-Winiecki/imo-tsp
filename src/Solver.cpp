#include "../include/Solver.h"

#include "../include/Instance.h"

int Solver::RandomInt(int min, int max) const
{
	return min + (rand() % (max - min));
}

int Solver::GetRandomNode() const
{
	return RandomInt(0, instance->Size());
}