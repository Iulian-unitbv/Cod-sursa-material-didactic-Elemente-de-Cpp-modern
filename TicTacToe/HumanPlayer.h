#pragma once
#include "Board.h"

#include <string>

class HumanPlayer
{
public:
	HumanPlayer(const std::string& name);

	Board::Position GetNextAction() const;

	const std::string& GetName() const;

private:
	std::string m_name;
};

