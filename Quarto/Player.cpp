#include "Player.h"

Player::Player(std::string&& name)
{
}

Piece Player::PickPiece(std::istream& is, UnusedPieces& unusedPieces)
{
	return Piece{ Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square };
}

Board::Position Player::PlacePiece(std::istream& is, Piece&& piece, Board& board)
{
	return Board::Position{};
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os;
}
