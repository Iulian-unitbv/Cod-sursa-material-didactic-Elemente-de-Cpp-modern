#include "AiPlayer.h"

AiPlayer::AiPlayer(const Board& board) : m_board(board)
{
	// empty
}

Board::Position AiPlayer::GetNextAction()
{
	std::vector<Board::Position> possibleActions = GetPossibleActions();
	return possibleActions.front();
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
