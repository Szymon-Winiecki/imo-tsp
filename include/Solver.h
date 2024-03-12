#pragma once

#include<cstdlib>

class Instance;
class Result;

class Solver 
{
public:
	Solver(Instance* instance) : Instance(instance, (unsigned int) time(NULL)) {}

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

	virtual Result* Solve() = 0;

private:

	inline int RandomInt(int min, int max) const;
	inline int GetRandomNode() const;

	Instance* instance;
};