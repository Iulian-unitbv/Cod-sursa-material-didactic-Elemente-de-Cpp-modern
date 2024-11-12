#include "AiPlayer.h"

#include <ranges>
#include <random>

namespace
{
	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());

	int64_t getStateActionHash(const Board& board, const Board::Position& position)
	{
		int64_t hash = 0;
		for (const auto& row : board)
		{
			for (const auto& pieceOptional : row)
			{
				if (pieceOptional.has_value())
				{
					switch (pieceOptional.value())
					{
					case Board::Piece::Cross:
						hash += 2;
						break;
					case Board::Piece::Nought:
						hash += 1;
						break;
					}
				}

				hash *= 10;
			}
		}

		auto& [line, column] = position;
		hash += line;
		hash *= 10;
		hash += column;

		return hash;
	}
}

AiPlayer::AiPlayer(const Board& board) : m_board(board)
{
	// empty
}

Board::Position AiPlayer::GetNextAction()
{
	std::vector<Board::Position> possibleActions = GetPossibleActions();
	std::reference_wrapper<Board::Position> bestAction = possibleActions.front();
	int64_t bestStateActionHash = -1;

	const float explorationRate = 0.1f;
	std::bernoulli_distribution bernDist(explorationRate);	// generates 'true' with explorationRate probability
	if (bernDist(randomEngine))
	{
		// randomly pick an action
		std::uniform_int_distribution<uint32_t> uniformDist(0, (uint32_t)possibleActions.size() - 1);
		bestAction = possibleActions[uniformDist(randomEngine)];
		bestStateActionHash = getStateActionHash(m_board, bestAction);
	}
	else
	{
		// compute best action
		float bestActionCost = -std::numeric_limits<float>::infinity();
		for (auto& action : possibleActions)
		{
			int64_t stateActionHash = getStateActionHash(m_board, action);
			float currentActionCost = m_stateActionCosts[stateActionHash];
			if (currentActionCost > bestActionCost)
			{
				bestAction = action;
				bestActionCost = currentActionCost;
				bestStateActionHash = stateActionHash;
			}
		}
	}

	m_previousStateActions.push_back(bestStateActionHash);

	return bestAction;
}

const std::string& AiPlayer::GetName() const
{
	static std::string name("AiPlayer");
	return name;
}

void AiPlayer::FeedReward(float target)
{
	const float learningRate = 0.1f;

	for (int64_t stateAction : m_previousStateActions | std::views::reverse)
	{
		float& cost = m_stateActionCosts[stateAction];
		cost += learningRate * (target - cost);
		target = cost;
	}

	m_previousStateActions.clear();
}

std::vector<Board::Position> AiPlayer::GetPossibleActions() const
{
	std::vector<Board::Position> possibleActions;
	for (uint8_t i = 0; i < Board::kRows; ++i)
	{
		for (uint8_t j = 0; j < Board::kColumns; ++j)
		{
			Board::Position position = { i, j };
			if (!m_board[position])
			{
				possibleActions.emplace_back(position);
			}
		}
	}

	return possibleActions;
}
