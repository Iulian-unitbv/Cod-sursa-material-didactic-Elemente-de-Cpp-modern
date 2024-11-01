#include "BoardStateChecker.h"

#include <algorithm>

namespace
{
	bool HaveSharedCharacteristics(const Board::LineView& view)
	{
		if (view.empty() || !std::ranges::all_of(view, &std::optional<Piece>::has_value))
			return false;

		constexpr size_t numCharacteristics{ 4 };
		std::array<bool, numCharacteristics> matchingCharacteristics;
		std::ranges::fill(matchingCharacteristics, true);

		auto it{ view.begin() };
		for (auto prev{ it++ }; it != view.end(); prev = it++)
		{
			matchingCharacteristics[0] &= (*prev)->GetBody() == (*it)->GetBody();
			matchingCharacteristics[1] &= (*prev)->GetColor() == (*it)->GetColor();
			matchingCharacteristics[2] &= (*prev)->GetHeight() == (*it)->GetHeight();
			matchingCharacteristics[3] &= (*prev)->GetShape() == (*it)->GetShape();
		}

		return std::ranges::any_of(matchingCharacteristics, std::identity());
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
