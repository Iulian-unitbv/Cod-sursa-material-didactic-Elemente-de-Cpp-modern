#pragma once
#include <string>

class Player
{
public:
	Player(std::string&& name);

	friend std::ostream& operator << (std::ostream& os, const Player& player);

private:
	std::string m_name;
};
