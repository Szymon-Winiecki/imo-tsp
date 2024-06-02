#pragma once

#include "Instance.h"
#include "CyclesContext.h"

#include <vector>
#include <array>
#include <memory>

class Result;

class EvolutionarySolution
{
public:
	EvolutionarySolution(Instance* instance, std::vector<std::vector<int>> cycles)
		: cycles{ cycles }
	{
		int iterations = 0;

		indexOfNode.resize(instance->Size());
		length = 0;

		for (int i = 0; i < cycles.size(); ++i)
		{
			int lastNode = cycles[i].back();

			for (int j = 0; j < cycles[i].size(); ++j)
			{
				indexOfNode[cycles[i][j]] = { i, j };
				length += instance->Distance(lastNode, cycles[i][j]);
				lastNode = cycles[i][j];
			}

			++iterations;
		}

		context = std::make_unique<CyclesContext>(instance, this->cycles, indexOfNode);
	}

	static std::shared_ptr<EvolutionarySolution> FromResult(Result* result);

	int GetLength() const;

	bool HasEdge(int nodeA, int nodeB) const;

	/*
	* Returns true if this solution is the same as other solution.
	* For now it only checks if the lengths are the same.
	*/
	bool isSame(std::shared_ptr<EvolutionarySolution> other) const;

	Result* GetResult() const;

	std::unique_ptr<CyclesContext> context;
	std::vector<std::vector<int>> cycles;
	
protected:
	int length;

	/*
	* At indexOfNode[n] there is an 2-element array {cycle, index} that indicates cycle in which node n is and its index in that cycle
	*/
	std::vector<std::array<int, 2>> indexOfNode;
};