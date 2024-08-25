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

		TEST_METHOD(SizeOfPieceEqualsOne)
		{
			Assert::AreEqual(1U, sizeof(Piece));
		}

		TEST_METHOD(PrintPiece)
		{
			Piece piece{ Piece::Body::Full, Piece::Color::Light, Piece::Height::Tall, Piece::Shape::Round };

			std::string expectedOutput = "0110";
			std::ostringstream stream;
			stream << piece;
			std::string actualOutput = stream.str();
			Assert::AreEqual(expectedOutput, actualOutput, L"If you see this message, piece is not printed correctly");
		}
	};
}
