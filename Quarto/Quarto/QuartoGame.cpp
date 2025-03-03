#include "QuartoGame.h"
#include "Player.h"
#include "BoardStateChecker.h"

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

    std::reference_wrapper<Player> pickingPlayer{ firstPlayer };
    auto placingPlayer{ std::ref(secondPlayer) };

	// update
	while (true)
	{
        std::system("cls");  // on Windows

        std::cout << "The board looks like this:" << std::endl;
        std::cout << board << std::endl;
        std::cout << "The unused pieces are the following:" << std::endl;
        std::cout << unusedPieces << std::endl;

        std::cout << pickingPlayer << ", which piece do you want to pick for " << placingPlayer << '?' << std::endl;

        std::optional<Piece> pickedPiece;
        while (true)
        {
            try
            {
                pickedPiece = Player::PickPiece(std::cin, unusedPieces);
                break;
            }
            catch (const std::out_of_range& exception)
            {
                std::cout << exception.what() << " Try again." << std::endl;
            }
        }

        std::cout << placingPlayer << ", where do you want to place the piece on the board?" << std::endl;

        Board::Position placedPosition;
        while (true)
        {
            try
            {
                try
                {
                    placedPosition = Player::PlacePiece(std::cin, std::move(pickedPiece.value()), board);
                    break;
                }
                catch (const std::invalid_argument&)
                {
                    // clear flags
                    std::cin.clear();
                    // ignore all further input, by moving to the end of the stream
                    std::cin.seekg(std::ios::end);
                    throw;
                }
            }
            catch (const std::exception& exception)
            {
                std::cout << exception.what() << " Try again." << std::endl;
            }
        }

        // check board state before swapping players and in case of end move, leave update loop
        BoardStateChecker::State state{ BoardStateChecker::Check(board, placedPosition) };
        if (state == BoardStateChecker::State::Win)
        {
            std::cout << "We have a winner!" << std::endl << "Congratulations: " << placingPlayer << std::endl;
            break;
        }
        else if (state == BoardStateChecker::State::Draw)
        {
            std::cout << "We have a draw! Congratulations to both players!" << std::endl;
            break;
        }

        std::swap(pickingPlayer, placingPlayer);
	}
}
