#pragma once

#include "Move.h"

class MoveComparator {
public:
	bool operator()(Move* a, Move* b) {
		if (a->GetGain() < b->GetGain()) {
			return true;
		}
		return false;
	}
};