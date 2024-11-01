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
	};
}
