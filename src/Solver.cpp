#include "../include/Solver.h"

#include "../include/Instance.h"

inline int Solver::RandomInt(int min, int max) const
{
	return min + (rand() % (max - min));
}

inline int Solver::GetRandomNode() const
{
	return RandomInt(0, instance->Size());
}