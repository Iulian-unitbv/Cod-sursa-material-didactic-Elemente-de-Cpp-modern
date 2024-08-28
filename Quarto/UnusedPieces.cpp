#include "UnusedPieces.h"

UnusedPieces::UnusedPieces()
{
}

Piece UnusedPieces::PickPiece(const std::string& name)
{
	return Piece{ Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round };
}

std::ostream& operator<<(std::ostream& os, const UnusedPieces& unusedPieces)
{
	return os;
}
