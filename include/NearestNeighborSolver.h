#pragma once

#include "Solver.h"

class Result;

class NearestNeighborSolver : Solver 
{
public:
	Result* Solve() override;


};