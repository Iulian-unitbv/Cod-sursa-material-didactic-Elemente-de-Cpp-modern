#include "BoardStateChecker.h"

namespace
{
	bool HaveSharedCharacteristics(const Board::LineView& view)
	{
		return false;
	}
}

BoardStateChecker::State BoardStateChecker::Check(const Board& board, const Board::Position& position)
{
	return State{};
}
