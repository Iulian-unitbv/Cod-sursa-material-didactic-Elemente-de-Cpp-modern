#include "Board.h"
#include <istream>

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
	constexpr char kEmptyCell[] = "____";
	for (auto& row : board.m_pieces)
	{
		for (auto& cell : row)
		{
			if (cell.has_value())
				os << cell.value();
			else
				os << kEmptyCell;
			os << ' ';
		}

		os << std::endl;
	}

	return os;
}

std::istream& operator >> (std::istream& is, Board::Position& position)
{
	// this little trick is needed here to read numbers instead of ASCII codes
	int64_t tempRow;
	int64_t tempColumn;
	if (is >> tempRow >> tempColumn)
	{
		using T = Board::PositionComponentType;
		if (tempRow >= std::numeric_limits<T>::min() &&
			tempRow <= std::numeric_limits<T>::max() &&
			tempColumn >= std::numeric_limits<T>::min() &&
			tempColumn <= std::numeric_limits<T>::max())
		{
			auto& [row, column] = position;
			row = static_cast<T>(tempRow);
			column = static_cast<T>(tempColumn);
		}
		else
			is.setstate(std::ios::failbit);
	}

	return is;
}
