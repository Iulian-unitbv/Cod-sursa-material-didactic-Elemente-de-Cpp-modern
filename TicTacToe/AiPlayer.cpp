#include "AiPlayer.h"

namespace
{
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
		}
	}

	return bestAction;
}

const std::string& AiPlayer::GetName() const
{
	static std::string name("AiPlayer");
	return name;
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
