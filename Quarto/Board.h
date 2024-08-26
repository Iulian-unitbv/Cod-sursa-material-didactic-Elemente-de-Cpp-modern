#pragma once
#include <array>
#include <optional>
#include <tuple>

#include "Piece.h"

class Board
{
public:
	using Position = std::tuple<uint8_t, uint8_t>;

public:
	Board() = default;

	// Getter
	const std::optional<Piece>& operator [] (const Position& position) const;
	// Getter/Setter
	std::optional<Piece>& operator [] (const Position& position);

private:
	static constexpr size_t kWidth = 4;
	static constexpr size_t kHeight = 4;

private:
	std::array<std::array<std::optional<Piece>, kWidth>, kHeight> m_pieces;
};
