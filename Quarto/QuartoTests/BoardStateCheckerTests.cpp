#include "CppUnitTest.h"

#include "BoardStateChecker.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
	// define shortcuts, to avoid huge line
	using Body = Piece::Body;
	using Color = Piece::Color;
	using Height = Piece::Height;
	using Shape = Piece::Shape;
	using State = BoardStateChecker::State;
}

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	// specialize ToString method to allow comparing State types in Assert::AreEqual
	template<>
	std::wstring ToString<State>(const State& state)
	{
		switch (state)
		{
		case State::Win:
			return ToString("Win");
		case State::Draw:
			return ToString("Draw");
		case State::None:
		default:
			return ToString("None");
		}
	}
}

namespace QuartoTests
{
	TEST_CLASS(BoardStateCheckerTests)
	{
	public:
        TEST_METHOD(NoneOnePiece)
        {
            Board board;
            Board::Position lastPosition{ 2, 1 };
            board[lastPosition] = Piece{ Body::Full, Color::Dark, Height::Short, Shape::Round };

            Assert::AreEqual(State::None, BoardStateChecker::Check(board, lastPosition));
        }

        TEST_METHOD(WinLineOne)
        {
            Board board;
            board[{0, 0}] = Piece{ Body::Full, Color::Dark, Height::Short, Shape::Round };
            board[{0, 1}] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Round };
            board[{0, 2}] = Piece{ Body::Full, Color::Dark, Height::Tall, Shape::Square };
            Board::Position lastPosition{ 0, 3 };
            board[lastPosition] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Square };

            Assert::AreEqual(State::Win, BoardStateChecker::Check(board, lastPosition));
        }

        TEST_METHOD(WinColumnThree)
        {
            Board board;
            board[{0, 2}] = Piece{ Body::Full, Color::Dark, Height::Short, Shape::Round };
            board[{1, 2}] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Round };
            board[{2, 2}] = Piece{ Body::Full, Color::Dark, Height::Tall, Shape::Square };
            Board::Position lastPosition{ 3, 2 };
            board[lastPosition] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Square };

            Assert::AreEqual(State::Win, BoardStateChecker::Check(board, lastPosition));
        }

        TEST_METHOD(WinMainDiagonal)
        {
            Board board;
            board[{0, 0}] = Piece{ Body::Full, Color::Dark, Height::Short, Shape::Round };
            board[{1, 1}] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Round };
            board[{2, 2}] = Piece{ Body::Full, Color::Dark, Height::Tall, Shape::Square };
            Board::Position lastPosition{ 3, 3 };
            board[lastPosition] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Square };

            Assert::AreEqual(State::Win, BoardStateChecker::Check(board, lastPosition));
        }

        TEST_METHOD(WinSecondaryDiagonal)
        {
            Board board;
            board[{0, 3}] = Piece{ Body::Full, Color::Dark, Height::Short, Shape::Round };
            board[{1, 2}] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Round };
            board[{2, 1}] = Piece{ Body::Full, Color::Dark, Height::Tall, Shape::Square };
            Board::Position lastPosition{ 3, 0 };
            board[lastPosition] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Square };

            Assert::AreEqual(State::Win, BoardStateChecker::Check(board, lastPosition));
        }

        TEST_METHOD(Draw)
        {
            Board board;
            board[{0, 0}] = Piece{ Body::Hollow, Color::Dark, Height::Tall, Shape::Square };
            board[{0, 1}] = Piece{ Body::Full, Color::Light, Height::Short, Shape::Round };
            board[{0, 2}] = Piece{ Body::Full, Color::Dark, Height::Tall, Shape::Square };
            board[{0, 3}] = Piece{ Body::Hollow, Color::Light, Height::Short, Shape::Round };

            board[{1, 0}] = Piece{ Body::Full, Color::Light, Height::Tall, Shape::Round };
            board[{1, 1}] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Square };
            board[{1, 2}] = Piece{ Body::Hollow, Color::Light, Height::Tall, Shape::Round };
            board[{1, 3}] = Piece{ Body::Full, Color::Dark, Height::Short, Shape::Square };

            board[{2, 0}] = Piece{ Body::Hollow, Color::Dark, Height::Tall, Shape::Round };
            board[{2, 1}] = Piece{ Body::Full, Color::Dark, Height::Tall, Shape::Round };
            board[{2, 2}] = Piece{ Body::Full, Color::Dark, Height::Short, Shape::Round };
            board[{2, 3}] = Piece{ Body::Hollow, Color::Light, Height::Tall, Shape::Square };

            board[{3, 0}] = Piece{ Body::Hollow, Color::Light, Height::Short, Shape::Square };
            board[{3, 1}] = Piece{ Body::Hollow, Color::Dark, Height::Short, Shape::Round };
            board[{3, 2}] = Piece{ Body::Full, Color::Light, Height::Tall, Shape::Square };
            Board::Position lastPosition{ 3, 3 };
            board[lastPosition] = Piece{ Body::Full, Color::Light, Height::Short, Shape::Square };

            Assert::AreEqual(State::Draw, BoardStateChecker::Check(board, lastPosition));
        }
	};
}
