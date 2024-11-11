#pragma once
#include "IPlayer.h"

#include <vector>
#include <unordered_map>

class AiPlayer : public IPlayer
{
public:
	AiPlayer(const Board& board);

	// Inherited via IPlayer
	Board::Position GetNextAction() override;
	const std::string& GetName() const override;

	void FeedReward(float target);

private:
	std::vector<Board::Position> GetPossibleActions() const;

private:
	const Board& m_board;
	std::unordered_map<int64_t, float> m_stateActionCosts;
	std::vector<int64_t> m_previousStateActions;
};
