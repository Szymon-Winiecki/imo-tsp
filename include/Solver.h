#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>

class Instance;
class Result;

class Solver 
{
public:
	Solver(Instance* instance) : Solver(instance, (unsigned int) time(NULL)) {}

	Solver(Instance* instance, unsigned int seed) : instance { instance } 
	{
		std::srand(seed);
	}

	void SetInstance(Instance* instance) 
	{
		this->instance = instance;
	}

	Instance* GetInstance() const {
		return instance;
	}

	virtual Result* Solve(int routes = 2) = 0;

protected:

	int RandomInt(int min, int max) const;
	int GetRandomNode() const;

	Instance* instance;
};