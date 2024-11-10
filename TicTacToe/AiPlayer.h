#pragma once
#include "IPlayer.h"

#include <vector>

class AiPlayer : public IPlayer
{
public:
	AiPlayer(const Board& board);

	// Inherited via IPlayer
	Board::Position GetNextAction() override;
	const std::string& GetName() const override;

private:
	std::vector<Board::Position> GetPossibleActions() const;

private:
	const Board& m_board;
};
