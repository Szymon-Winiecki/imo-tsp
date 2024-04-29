#pragma once

#include "Move.h"

class MoveComparator {
public:
	bool operator()(std::shared_ptr<Move> a, std::shared_ptr<Move> b) {
		if (a->GetGain() < b->GetGain()) {
			return true;
		}
		return false;
	}
};