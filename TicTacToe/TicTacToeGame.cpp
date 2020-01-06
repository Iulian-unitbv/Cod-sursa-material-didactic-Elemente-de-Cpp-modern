#include "TicTacToeGame.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "ConsoleRenderer.h"

void TicTacToeGame::Run()
{
	Board board;
	HumanPlayer player1("Player 1");
	HumanPlayer player2("Player 2");

	ConsoleRenderer renderer;

	std::reference_wrapper<HumanPlayer> currentPlayer = player1;
	std::reference_wrapper<HumanPlayer> nextPlayer = player2;
	Board::Piece currentPiece = Board::Piece::Cross;
	Board::Piece nextPiece = Board::Piece::Nought;

	bool isGameActive = true;
	while (isGameActive)
	{
		renderer.Draw(board);
		bool isInputOk = false;
		while (!isInputOk)
		{
			const Board::Position& position = currentPlayer.get().GetNextAction();
			if (!board[position])
			{
				board[position] = currentPiece;
				isInputOk = true;
			}
		}

		auto state = board.Check();
		switch (state)
		{
		case Board::State::Win:
			renderer.ShowEndScreen(currentPlayer);
			isGameActive = false;
			break;
		case Board::State::Draw:
			renderer.ShowEndScreen();
			isGameActive = false;
			break;
		case Board::State::None:
			std::swap(currentPlayer, nextPlayer);
			std::swap(currentPiece, nextPiece);
		}
	}
}
