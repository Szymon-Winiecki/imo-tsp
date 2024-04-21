#pragma once

class CyclesContext;

#include <vector>
#include <array>

class Move
{
public:
	Move(CyclesContext* context);
	int GetGain() const;
	virtual bool IsApplicable() const = 0;
	virtual bool ShouldRemove() const = 0;
	virtual int Apply() = 0;
	virtual std::vector<int> GetAffectedNodes() = 0;
	virtual std::vector < std::array<int, 2>> GetNewEdges() = 0;

	bool operator <(Move const& rhs);

protected:
	CyclesContext* context;
	int gain;
};