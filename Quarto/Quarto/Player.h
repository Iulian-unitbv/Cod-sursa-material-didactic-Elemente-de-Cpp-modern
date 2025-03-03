#pragma once
#include "Board.h"
#include "UnusedPieces.h"

class Player
{
public:
	Player(std::string&& name);

	// Used when a player must choose a piece from the pool of unused pieces.
	// The piece is removed from the pool of unused pieces and returned.
	// An std::out_of_range exception is thrown if the input is not among the unsused pieces.
	static Piece PickPiece(std::istream& is, UnusedPieces& unusedPieces);

	// Used when the player must place a piece on the board.
	// The function takes ownership of the piece and moves it to the board.
	// The position on the board (line, column) where the piece has been placed is returned.
	// Can throw: std::invalid_argument for wrong input, std::out_of_range for out of bounds positions,
	// or std::logic_error if the requested position is ocupied
	static Board::Position PlacePiece(std::istream& is, Piece&& piece, Board& board);

	friend std::ostream& operator << (std::ostream& os, const Player& player);

private:
	std::string m_name;
};
