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
	const auto& [row, column] = position;
	const Board::LineView& rowView{ board.GetRowView(row) };

	return
		HaveSharedCharacteristics(rowView) ||
		HaveSharedCharacteristics(board.GetColumnView(column)) ||
		row == column && HaveSharedCharacteristics(board.GetMainDiagonalView()) ||
		row == (rowView.size() - column - 1) && HaveSharedCharacteristics(board.GetSecondaryDiagonalView()) ?
		BoardStateChecker::State::Win :
		board.IsFull() ?
		BoardStateChecker::State::Draw :
		BoardStateChecker::State::None;
}
