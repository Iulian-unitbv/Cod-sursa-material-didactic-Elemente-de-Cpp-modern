#pragma once
#include <array>
#include <functional>
#include <optional>
#include <ranges>
#include <tuple>

#include "Piece.h"

class Board
{
public:
	using Position = std::tuple<uint8_t, uint8_t>;
	using BoardTransformer = std::function<const std::optional<Piece>& (size_t)>;
	using LineView = std::ranges::transform_view<std::ranges::iota_view<size_t, size_t>, BoardTransformer>;

public:
	Board() = default;

	// Getter
	const std::optional<Piece>& operator [] (const Position& position) const;
	// Getter/Setter
	std::optional<Piece>& operator [] (const Position& position);

	// Views
	LineView GetRowView(uint8_t row) const;
	LineView GetColumnView(uint8_t column) const;
	LineView GetMainDiagonalView() const;
	LineView GetSecondaryDiagonalView() const;

	bool IsFull() const;

	friend std::ostream& operator << (std::ostream& os, const Board& board);

private:
	LineView GetLineView(BoardTransformer&& transformer) const;

	static constexpr size_t kWidth = 4;
	static constexpr size_t kHeight = 4;

private:
	std::array<std::array<std::optional<Piece>, kWidth>, kHeight> m_pieces;
};
