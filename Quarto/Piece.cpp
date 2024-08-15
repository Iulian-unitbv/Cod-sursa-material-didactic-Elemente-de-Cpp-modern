#include "Piece.h"

Piece::Piece(Body body, Color color, Height height, Shape shape) :
	m_body{ body },
	m_color{ color },
	m_height{ height },
	m_shape{ shape }
{
	// empty
}