#include "CppUnitTest.h"

#include "UnusedPieces.h"

#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuartoTests
{
	TEST_CLASS(UnusedPiecesTests)
	{
	public:
		TEST_METHOD(ConstructAndPrint)
		{
			UnusedPieces unusedPieces;

			auto expectedPieces = {
				"0000", "0001", "0010", "0011",
				"0100", "0101", "0110", "0111",
				"1000", "1001", "1010", "1011",
				"1100", "1101", "1110", "1111"
			};

			std::ostringstream stream;
			stream << unusedPieces;
			std::string output{ stream.str() };

			// make sure there are enough spaces in the output - potentially after each piece
			Assert::AreEqual<size_t>(
				expectedPieces.size(),
				std::count(output.begin(), output.end(), ' '),
				L"Didn't find the expected number of spaces."
				);

			// make sure all the expected pieces are in the output
			for (const char* pieceName : expectedPieces)
			{
				std::wostringstream assertMessageStream;
				assertMessageStream << pieceName << " not found in expected pieces.";
				Assert::IsTrue(
					output.find(pieceName) != std::string::npos,
					assertMessageStream.str().c_str()
				);
			}
		}

		TEST_METHOD(ConstructPickAndPrint)
		{
			UnusedPieces unusedPieces;

			unusedPieces.PickPiece("0000");
			unusedPieces.PickPiece("1001");
			unusedPieces.PickPiece("1111");

			auto expectedPieces = {
				"0001", "0010", "0011",
				"0100", "0101", "0110", "0111",
				"1000", "1010", "1011",
				"1100", "1101", "1110"
			};

			std::ostringstream stream;
			stream << unusedPieces;
			std::string output{ stream.str() };

			// make sure all the expected pieces are in the output
			for (const char* pieceName : expectedPieces)
			{
				Assert::IsTrue(output.find(pieceName) != std::string::npos);
			}
		}

		TEST_METHOD(PickInvalidPiece)
		{
			UnusedPieces unusedPieces;

			Assert::ExpectException<std::out_of_range>(
				[&unusedPieces]() { unusedPieces.PickPiece("abcd"); }
			);
		}

		TEST_METHOD(PickSamePieceTwice)
		{
			UnusedPieces unusedPieces;

			unusedPieces.PickPiece("1101");

			Assert::ExpectException<std::out_of_range>(
				[&unusedPieces]() { unusedPieces.PickPiece("1101"); }
			);
		}
	};
}
