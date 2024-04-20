#pragma once

class CyclesContext;

#include <vector>

class Move
{
public:
	Move(CyclesContext* context);
	int GetGain() const;
	virtual bool IsApplicable() const = 0;
	virtual int Apply() = 0;

	bool operator <(Move const& rhs);

protected:
	CyclesContext* context;
	int gain;
};