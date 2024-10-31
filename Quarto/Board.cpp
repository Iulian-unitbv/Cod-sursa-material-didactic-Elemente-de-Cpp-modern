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

Board::LineView Board::GetRowView(uint8_t row) const
{
	return Board::LineView{};
}

Board::LineView Board::GetColumnView(uint8_t column) const
{
	return Board::LineView{};

}

Board::LineView Board::GetMainDiagonalView() const
{
	return Board::LineView{};

}

Board::LineView Board::GetSecondaryDiagonalView() const
{
	return Board::LineView{};

}

bool Board::IsFull() const
{
	return false;
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

Board::LineView Board::GetLineView(BoardTransformer&& transformer) const
{
	return Board::LineView{};
}
