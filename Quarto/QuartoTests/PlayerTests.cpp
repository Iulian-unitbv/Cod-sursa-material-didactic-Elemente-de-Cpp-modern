#include "CppUnitTest.h"
#include "Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<class TChar>
std::basic_ostream<TChar>& operator << (std::basic_ostream<TChar>& out, const Board::Position& position)
{
	auto& [row, column] = position;
	// convert from 'uint_8' which is a 'char', to int, so the stream has the actual number not the ASCII value of a 'char'
	return out << static_cast<int>(row) << ' ' << static_cast<int>(column);
}

template<>
std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Board::Position>(const Board::Position& position)
{
	RETURN_WIDE_STRING(position);
}

namespace QuartoTests
{
	TEST_CLASS(PlayerTests)
	{
	public:
		
		TEST_METHOD(ConstructorTakesOwnership)
		{
			std::string playerName{ "Player One" };
			Player player{ std::move(playerName) };

			Assert::IsTrue(playerName.empty());
		}

		TEST_METHOD(PrintPlayer)
		{
			std::string playerName{ "Player Two" };
			std::string expectedOutput{ playerName };
			Player player{ std::move(playerName) };
			std::ostringstream stream;

			stream << player;
			std::string actualOutput{ stream.str() };

			Assert::AreEqual(expectedOutput, actualOutput);
		}

		TEST_METHOD(PickPieceOk)
		{
			UnusedPieces unusedPieces;
			Player player{ "Picking Player" };
			std::stringstream stream;
			stream << "0101";

			Piece piece{ player.PickPiece(stream, unusedPieces) };

			Assert::ExpectException<std::out_of_range>(
				[&unusedPieces]() { unusedPieces.PickPiece("0101"); }
			);
			Assert::IsFalse(stream.fail());
			Assert::IsTrue(Piece::Body::Full == piece.GetBody());
			Assert::IsTrue(Piece::Color::Light == piece.GetColor());
			Assert::IsTrue(Piece::Height::Short == piece.GetHeight());
			Assert::IsTrue(Piece::Shape::Square == piece.GetShape());
		}

		TEST_METHOD(PickUnavailablePiece)
		{
			std::string pieceName{ "0110" };
			UnusedPieces unusedPieces;
			unusedPieces.PickPiece(pieceName);
			Player player{ "Picking Player" };
			std::stringstream stream;
			stream << pieceName;

			Assert::ExpectException<std::out_of_range>(
				[&player, &stream, &unusedPieces]() {
					player.PickPiece(stream, unusedPieces);
				}
			);
			Assert::IsFalse(stream.fail());
		}

		TEST_METHOD(PlacePieceOk)
		{
			Player player{ "Placing Player" };
			Board::Position expectedPosition{ 2, 1 };
			std::stringstream stream;
			stream << expectedPosition;
			Board board;
			Piece piece{ Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square };

			Board::Position actualPosition = player.PlacePiece(stream, std::move(piece), board);

			Assert::IsFalse(stream.fail());
			std::optional<Piece> pieceOpt = board[expectedPosition];
			Assert::IsTrue(pieceOpt.has_value());
			Assert::IsTrue(Piece::Body::Hollow == pieceOpt->GetBody());
			Assert::IsTrue(Piece::Color::Dark == pieceOpt->GetColor());
			Assert::IsTrue(Piece::Height::Short == pieceOpt->GetHeight());
			Assert::IsTrue(Piece::Shape::Square == pieceOpt->GetShape());
			Assert::AreEqual(expectedPosition, actualPosition);
		}

		TEST_METHOD(PlacePieceOnOcupiedPosition)
		{
			Player player{ "Placing Player" };
			Board::Position ocupiedPosition{ 2, 2 };
			std::stringstream stream;
			stream << ocupiedPosition;
			Board board;
			board[ocupiedPosition] = Piece{ Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round };
			Piece piece{ Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square };

			Assert::ExpectException<std::logic_error>(
				[&player, &stream, &piece, &board]() {
					player.PlacePiece(stream, std::move(piece), board);
				}
			);
			Assert::IsFalse(stream.fail());
		}

		TEST_METHOD(PlacePieceOnOutOfBoundsPosition)
		{
			Player player{ "Placing Player" };
			Board::Position position{ 0, 5 };
			std::stringstream stream;
			stream << position;
			Board board;
			Piece piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);

			Assert::ExpectException<std::out_of_range>(
				[&player, &stream, &piece, &board]() {
					player.PlacePiece(stream, std::move(piece), board);
				}
			);
			Assert::IsFalse(stream.fail());
		}

		TEST_METHOD(PlacePieceOnGarbagePosition)
		{
			Player player{ "Placing Player" };
			std::stringstream stream;
			stream << 'g' << ' ' << "arbage";
			Board board;
			Piece piece{ Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square };

			Assert::ExpectException<std::invalid_argument>(
				[&player, &stream, &piece, &board]() {
					player.PlacePiece(stream, std::move(piece), board);
				}
			);
			Assert::IsTrue(stream.fail());
		}
	};
}
