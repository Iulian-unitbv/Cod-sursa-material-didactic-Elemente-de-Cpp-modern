#include "Board.h"

const std::optional<Piece>& Board::operator [] (const Position& position) const
{
	return std::nullopt;
}

std::optional<Piece>& Board::operator [] (const Position& position)
{
	static std::optional<Piece> dummy;
	return dummy;
}

std::ostream& operator << (std::ostream& os, const Board& board)
{
	return os;
}
