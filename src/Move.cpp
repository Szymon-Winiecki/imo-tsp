#include "../include/Move.h"

Move::Move(CyclesContext* context)
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
