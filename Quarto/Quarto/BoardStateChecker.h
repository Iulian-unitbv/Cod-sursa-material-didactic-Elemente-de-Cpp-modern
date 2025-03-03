#pragma once
#include "Board.h"

class BoardStateChecker
{
public:
    enum class State : std::uint8_t
    {
        None,
        Win,
        Draw
    };

public:
    static State Check(const Board& board, const Board::Position& position);
};
