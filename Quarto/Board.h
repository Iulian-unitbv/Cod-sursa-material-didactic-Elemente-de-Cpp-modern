#pragma once
#include <array>
#include <optional>

#include "Piece.h"

class Board
{
private:
	static constexpr size_t kWidth = 4;
	static constexpr size_t kHeight = 4;

private:
	std::array<std::array<std::optional<Piece>, kWidth>, kHeight> m_pieces;
};
