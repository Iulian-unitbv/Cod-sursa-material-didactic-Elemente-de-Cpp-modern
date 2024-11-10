#include "AiPlayer.h"

Board::Position AiPlayer::GetNextAction()
{
	return { 2, 2 };
}

const std::string& AiPlayer::GetName() const
{
	static std::string name("AiPlayer");
	return name;
}
