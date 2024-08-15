#include "CppUnitTest.h"

#include "Piece.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuartoTests
{
	TEST_CLASS(PieceTests)
	{
	public:
		TEST_METHOD(ConstructorAndGetters)
		{
			Piece piece{ Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square };

			Assert::IsTrue(Piece::Body::Full == piece.GetBody());
			Assert::IsTrue(Piece::Color::Dark == piece.GetColor());
			Assert::IsTrue(Piece::Height::Short == piece.GetHeight());
			Assert::IsTrue(Piece::Shape::Square == piece.GetShape());
		}
	};
}
