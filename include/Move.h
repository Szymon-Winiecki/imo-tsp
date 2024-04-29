#pragma once

class CyclesContext;

#include <vector>
#include <array>
#include <memory>

class Move
{
public:
	Move(std::shared_ptr<CyclesContext> context);
	int GetGain() const;
	virtual bool IsApplicable() const = 0;
	virtual bool ShouldRemove() const = 0;
	virtual int Apply() = 0;
	virtual std::vector<int> GetAffectedNodes() = 0;
	virtual std::vector < std::array<int, 2>> GetNewEdges() = 0;

	bool operator <(Move const& rhs);

protected:
	std::shared_ptr<CyclesContext> context;
	int gain;
};