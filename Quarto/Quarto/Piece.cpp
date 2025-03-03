#include "Piece.h"

Piece::Piece(Body body, Color color, Height height, Shape shape) :
	m_body{ body },
	m_color{ color },
	m_height{ height },
	m_shape{ shape }
{
	static_assert(sizeof(*this) == 1, "This class should be 1 byte in size");
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
	return os
		<< static_cast<int>(piece.GetBody())
		<< static_cast<int>(piece.GetColor())
		<< static_cast<int>(piece.GetHeight())
		<< static_cast<int>(piece.GetShape());
}
