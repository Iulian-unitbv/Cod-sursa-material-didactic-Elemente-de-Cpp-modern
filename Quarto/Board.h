#pragma once
#include <array>
#include <optional>
#include <tuple>

#include "Piece.h"

class Board
{
public:
	using PositionComponentType = uint8_t;
	using Position = std::tuple<PositionComponentType, PositionComponentType>;

public:
	Board() = default;

	// Getter
	const std::optional<Piece>& operator [] (const Position& position) const;
	// Getter/Setter
	std::optional<Piece>& operator [] (const Position& position);

	friend std::ostream& operator << (std::ostream& os, const Board& board);

private:
	static constexpr size_t kWidth = 4;
	static constexpr size_t kHeight = 4;

private:
	std::array<std::array<std::optional<Piece>, kWidth>, kHeight> m_pieces;
};

std::istream& operator >> (std::istream& is, Board::Position& position);
