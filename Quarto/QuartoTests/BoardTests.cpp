#include "CppUnitTest.h"

#include <algorithm>
#include <ranges>
#include <vector>

#include "Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using enum Piece::Body;
using enum Piece::Color;
using enum Piece::Height;
using enum Piece::Shape;

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
			Piece piece{ Hollow, Dark, Short, Square };
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
			board[{1, 2}] = Piece{ Hollow, Light, Short, Round };

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

		TEST_METHOD(ViewRow)
		{
			auto expectedPieces = {
				Piece{ Hollow, Light, Short, Round  },
				Piece{ Full,   Light, Short, Round  },
				Piece{ Hollow, Dark,  Short, Round  },
				Piece{ Hollow, Light, Short, Square }
			};
			Board board;
			constexpr uint8_t row{ 2 };
			for (uint8_t column{ 0 }; const auto & expectedPiece : expectedPieces)
			{
				board[{row, column++}] = expectedPiece;
			}

			Assert::IsTrue(std::ranges::equal(expectedPieces, board.GetRowView(row), ComparePieces));
		}

		TEST_METHOD(ViewColumn)
		{
			auto expectedPieces = {
				Piece{ Hollow, Light, Short, Round  },
				Piece{ Full,   Light, Short, Round  },
				Piece{ Hollow, Dark,  Short, Round  },
				Piece{ Hollow, Light, Short, Square }
			};
			Board board;
			constexpr uint8_t column{ 2 };
			for (uint8_t row{ 0 }; const auto & expectedPiece : expectedPieces)
			{
				board[{row++, column}] = expectedPiece;
			}

			Assert::IsTrue(std::ranges::equal(expectedPieces, board.GetColumnView(column), ComparePieces));
		}

		TEST_METHOD(ViewMainDiagonal)
		{
			auto expectedPieces = {
				Piece{ Hollow, Light, Short, Round  },
				Piece{ Full,   Light, Short, Round  },
				Piece{ Hollow, Dark,  Short, Round  },
				Piece{ Hollow, Light, Short, Square }
			};
			Board board;
			for (uint8_t index{ 0 }; const auto & expectedPiece : expectedPieces)
			{
				board[{index, index}] = expectedPiece;
				++index;
			}

			Assert::IsTrue(std::ranges::equal(expectedPieces, board.GetMainDiagonalView(), ComparePieces));
		}

		TEST_METHOD(ViewSecondaryDiagonal)
		{
			auto expectedPieces = {
				Piece{ Hollow, Light, Short, Round  },
				Piece{ Full,   Light, Short, Round  },
				Piece{ Hollow, Dark,  Short, Round  },
				Piece{ Hollow, Light, Short, Square }
			};
			Board board;
			uint8_t width = uint8_t(expectedPieces.size());
			for (uint8_t index{ 0 }; const auto & expectedPiece : expectedPieces)
			{
				board[{index, width - index - 1}] = expectedPiece;
				++index;
			}

			Assert::IsTrue(std::ranges::equal(expectedPieces, board.GetSecondaryDiagonalView(), ComparePieces));
		}

		TEST_METHOD(IsFull)
		{
			Board board;
			for (uint8_t row : {0, 1, 2, 3})
				for (uint8_t column : {0, 1, 2, 3})
					board[{row, column}] = Piece{ Hollow, Light, Short, Round };

			Assert::IsTrue(board.IsFull());
		}

		TEST_METHOD(IsNotFull)
		{
			Board board;
			for (uint8_t row : {0, 1, 2, 3})
				for (uint8_t column : {0, 1, 2})
					board[{row, column}] = Piece{ Hollow, Light, Short, Round };

			Assert::IsFalse(board.IsFull());
		}

	private:
		static bool ComparePieces(const Piece& left, const std::optional<Piece>& right)
		{
			return
				right.has_value() &&
				left.GetBody() == right->GetBody() &&
				left.GetColor() == right->GetColor() &&
				left.GetHeight() == right->GetHeight() &&
				left.GetShape() == right->GetShape();
		}
	};
}
