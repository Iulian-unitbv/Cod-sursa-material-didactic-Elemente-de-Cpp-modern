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
	return GetLineView(
		[this, row](size_t index) -> const std::optional<Piece>& {
			return (*this)[{row, static_cast<uint8_t>(index)}];
		}
	);
}

Board::LineView Board::GetColumnView(uint8_t column) const
{
	return GetLineView(
		[this, column](size_t index) -> const std::optional<Piece>& {
			return(*this)[{static_cast<uint8_t>(index), column}];
		}
	);
}

Board::LineView Board::GetMainDiagonalView() const
{
	static_assert(kWidth == kHeight);
	return GetLineView(
		[this](size_t index) -> const std::optional<Piece>& {
			return m_pieces[index][index];
		}
	);
}

Board::LineView Board::GetSecondaryDiagonalView() const
{
	static_assert(kWidth == kHeight);
	return GetLineView(
		[this](size_t index) -> const std::optional<Piece>& {
			return m_pieces[index][kWidth - index - 1];
		}
	);
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
	return
		std::views::iota(0u, kWidth) |
		std::views::transform(std::move(transformer));
}
