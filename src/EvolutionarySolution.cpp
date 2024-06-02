#include "../include/EvolutionarySolution.h"

#include "../include/CyclesContext.h"
#include "../include/Result.h"

std::shared_ptr<EvolutionarySolution> EvolutionarySolution::FromResult(Result* result)
{
	return std::make_shared<EvolutionarySolution>(result->GetInstance(), result->GetCycles());
}

int EvolutionarySolution::GetLength() const
{
	return length;
}

bool EvolutionarySolution::HasEdge(int nodeA, int nodeB) const
{
	if (context->IsEdge(nodeA, nodeB))
	{
		return true;
	}
	return false;
}

bool EvolutionarySolution::isSame(std::shared_ptr<EvolutionarySolution> other) const
{
	return length == other->length;
}

Result* EvolutionarySolution::GetResult() const
{
	Result* result = new Result(context->GetInstance(), cycles.size());

	for (int i = 0; i < cycles.size(); ++i)
	{
		int lastNode = -1;

		for (auto node : cycles[i])
		{
			if (lastNode != -1)
			{
				result->AddEdge(i, lastNode, node);
			}
			lastNode = node;
		}
		result->AddEdge(i, lastNode, cycles[i].front());
	}

	return result;
}
