#include "CppUnitTest.h"

#include <vector>

#include "Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuartoTests
{
	TEST_CLASS(BoardTests)
	{
	public:
		TEST_METHOD(DefaultConstructorEmpty4x4Board)
		{
			Board board;
			for (uint8_t i : {0, 1, 2, 3})
				for (uint8_t j : {0, 1, 2, 3})
					if (board[{i, j}].has_value())
						Assert::Fail();
		}

		TEST_METHOD(SetGetAtOneOne)
		{
			Board board;
			Piece piece{ Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square };
			Board::Position position{ 1, 1 };

			// test setter
			board[position] = piece;

			// test getter
			Assert::IsTrue(board[position].has_value());

			const Board& constBoard{ board };
			// test const getter
			const Piece& retrievedPiece{ constBoard[position].value() };

			// test retrieved piece
			Assert::IsTrue(
				retrievedPiece.GetBody() == piece.GetBody() &&
				retrievedPiece.GetColor() == piece.GetColor() &&
				retrievedPiece.GetHeight() == piece.GetHeight() &&
				retrievedPiece.GetShape() == piece.GetShape()
			);
		}

		TEST_METHOD(AccessOutOfBoundsPositions)
		{
			Board board;
			std::vector<Board::Position> badPositions{
				{-1, 0}, {0, -1}, {-1, -1}, {4, 3}, {3, 4}, {4, 4}
			};

			for (const Board::Position& position : badPositions)
			{
				// test getter/setter
				Assert::ExpectException<std::out_of_range>(
					[&board, &position]() { board[position]; }
				);
			}

			const Board constBoard;
			for (const Board::Position& position : badPositions)
			{
				// test const getter
				Assert::ExpectException<std::out_of_range>(
					[&constBoard, &position]() { constBoard[position]; }
				);
			}
		}

		TEST_METHOD(PrintBoard)
		{
			Board board;
			board[{1, 2}] = Piece{ Piece::Body::Hollow, Piece::Color::Light, Piece::Height::Short, Piece::Shape::Round };

			std::string expectedOutput{
				"____ ____ ____ ____ \n"
				"____ ____ 1100 ____ \n"
				"____ ____ ____ ____ \n"
				"____ ____ ____ ____ \n"
			};

			std::ostringstream stream;
			stream << board;
			std::string actualOutput{ stream.str() };

			Assert::AreEqual(expectedOutput, actualOutput);
		}
	};
}
