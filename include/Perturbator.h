#pragma once

#include <vector>

class Perturbator
{
public:
	virtual void Perturbate(std::vector<std::vector<int>>& cycles) = 0;
};