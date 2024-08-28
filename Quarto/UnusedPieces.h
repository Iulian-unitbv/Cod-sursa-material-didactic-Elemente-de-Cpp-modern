#pragma once

#include "Piece.h"

#include <unordered_map>

// Holds all the unused pieces throughout a game.
class UnusedPieces
{
private:
	std::unordered_map<std::string, Piece> m_pool;
};
