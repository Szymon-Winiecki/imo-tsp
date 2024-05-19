#include "../include/RandomPerturbator.h"

void RandomPerturbator::Perturbate(std::vector<std::vector<int>>& cycles)
{
	for (int i = 0; i < numChanges; i++)
	{
		int cycleA = rand() % cycles.size();
		int nodeAIndex = rand() % cycles[cycleA].size();
		int cycleB = rand() % cycles.size();
		int nodeBIndex = rand() % cycles[cycleB].size();

		if (cycleA != cycleB)
		{
			SwapNodes(cycles, cycleA, nodeAIndex, cycleB, nodeBIndex);
		}
		else if (rand() % 2)
		{
			SwapNodes(cycles, cycleA, nodeAIndex, cycleB, nodeBIndex);
		}
		else
		{
			SwapEdges(cycles, cycleA, nodeAIndex, nodeBIndex);
		}
	}
}

void RandomPerturbator::SwapNodes(std::vector<std::vector<int>>& cycles, int cycleA, int nodeAIndex, int cycleB, int nodeBIndex)
{
	std::swap(cycles[cycleA][nodeAIndex], cycles[cycleB][nodeBIndex]);
}

void RandomPerturbator::SwapEdges(std::vector<std::vector<int>>& cycles, int cycle, int edgeAIndex, int edgeBIndex)
{
	if (edgeAIndex > edgeBIndex)
	{
		std::swap(edgeAIndex, edgeBIndex);
	}

	std::reverse(cycles[cycle].begin() + edgeAIndex + 1, cycles[cycle].begin() + edgeBIndex + 1);
}
