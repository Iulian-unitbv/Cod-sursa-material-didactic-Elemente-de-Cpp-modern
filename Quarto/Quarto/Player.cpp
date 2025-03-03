#include "Player.h"
#include <sstream>

Player::Player(std::string&& name) : m_name{ std::move(name) }
{
	// empty
}

Piece Player::PickPiece(std::istream& is, UnusedPieces& unusedPieces)
{
	std::string pickedPieceName;
	is >> pickedPieceName;
	Piece pickedPiece{ unusedPieces.PickPiece(pickedPieceName) };
	return std::move(pickedPiece);
}

Board::Position Player::PlacePiece(std::istream& is, Piece&& piece, Board& board)
{
	// this little trick is needed here to read numbers instead of ASCII codes
	uint16_t row;
	uint16_t column;

	if (is >> row >> column)
	{
		Board::Position position{ static_cast<uint8_t>(row), static_cast<uint8_t>(column) };
		std::optional<Piece>& pieceOpt{ board[position] };

		if (pieceOpt)
			throw std::logic_error{ "The position is occupied by another piece." };

		pieceOpt = std::move(piece);

		return position;
	}

	throw std::invalid_argument{ "Only numbers are accepted." };
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << player.m_name;
}
