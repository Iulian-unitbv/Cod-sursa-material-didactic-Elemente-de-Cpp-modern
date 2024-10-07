#include "QuartoGame.h"
#include "Player.h"

#include <iostream>

void QuartoGame::Run()
{
	// initialization
    Board board;
    UnusedPieces unusedPieces;

    std::string playerName;
    std::cout << "First player name: ";
    std::cin >> playerName;
	Player firstPlayer{ std::move(playerName) };

	std::cout << "Second player name: ";
	std::cin >> playerName;
	Player secondPlayer{ std::move(playerName) };

	// update
	while (true)
	{
		Piece pickedPiece{ Player::PickPiece(std::cin, unusedPieces) };
        Player::PlacePiece(std::cin, std::move(pickedPiece), board);
	}
}
