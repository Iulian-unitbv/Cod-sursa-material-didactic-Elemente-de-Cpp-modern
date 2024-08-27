#include "Board.h"

const std::optional<Piece>& Board::operator [] (const Position& position) const
{
	const auto& [row, column] = position;
	if (row < 0 || row >= kHeight || column < 0 || column >= kWidth)
		throw std::out_of_range{ "Board position out of bounds." };

	return m_pieces[row][column];
}

std::optional<Piece>& Board::operator [] (const Position& position)
{
	return const_cast<std::optional<Piece>&>(std::as_const(*this)[position]);
}

std::ostream& operator << (std::ostream& os, const Board& board)
{
	return os;
}
