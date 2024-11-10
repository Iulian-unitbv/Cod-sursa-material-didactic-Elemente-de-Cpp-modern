#pragma once
#include "IPlayer.h"

class AiPlayer : public IPlayer
{
public:
	// Inherited via IPlayer
	Board::Position GetNextAction() override;
	const std::string& GetName() const override;
};
