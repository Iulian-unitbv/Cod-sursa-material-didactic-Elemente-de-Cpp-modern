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
        std::system("cls");  // on Windows

        std::cout << "The board looks like this:" << std::endl;
        std::cout << board << std::endl;
        std::cout << "The unused pieces are the following:" << std::endl;
        std::cout << unusedPieces << std::endl;

        std::cout << firstPlayer << ", which piece do you want to pick for " << secondPlayer << '?' << std::endl;
		Piece pickedPiece{ Player::PickPiece(std::cin, unusedPieces) };

        std::cout << secondPlayer << ", where do you want to place the piece on the board?" << std::endl;
        Player::PlacePiece(std::cin, std::move(pickedPiece), board);
	}
}
