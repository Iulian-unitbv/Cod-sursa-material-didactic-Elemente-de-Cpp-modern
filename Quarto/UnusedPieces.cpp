#include "UnusedPieces.h"

#include <ranges>
#include <sstream>

UnusedPieces::UnusedPieces()
{
	for (Piece::Body body : {Piece::Body::Full, Piece::Body::Hollow})
		for (Piece::Color color : {Piece::Color::Dark, Piece::Color::Light})
			for (Piece::Height height : {Piece::Height::Short, Piece::Height::Tall})
				for (Piece::Shape shape : {Piece::Shape::Round, Piece::Shape::Square})
				{
					Piece piece{ body, color, height, shape };
					std::ostringstream stream;
					stream << piece;
					m_pool.emplace(stream.str(), std::move(piece));
				}
}

Piece UnusedPieces::PickPiece(const std::string& name)
{
	if (auto node{ m_pool.extract(name) }; node)
		return std::move(node.mapped());
	else
		throw std::out_of_range{ "Piece not found." };
}

std::ostream& operator<<(std::ostream& os, const UnusedPieces& unusedPieces)
{
	for (const auto& pieceName : std::views::keys(unusedPieces.m_pool))
		os << pieceName << ' ';
	return os;
}
