#include "../include/Move.h"

Move::Move(std::shared_ptr<CyclesContext> context)
	:context{ context } 
{}

bool Move::operator<(Move const& rhs)
{
	return gain < rhs.gain;
}

int Move::GetGain() const
{
	return gain;
}
