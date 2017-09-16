#include "catch.hpp"

#include "matchers.h"
#include "Shapes/shapes.h"

TEST_CASE("CheckCharsValidation", "[shapes]")
{
    const auto result = Shapes::recognize("x", 1, 1);
    CHECK(result.has_error());
    CHECK(result.error() == Shapes::Error::InvalidData);
}

TEST_CASE("CheckDataSizeIsValidated", "[shapes]")
{
    const auto result = Shapes::recognize("0011", 10, 10);
    CHECK(result.has_error());
    CHECK(result.error() == Shapes::Error::InvalidDimensions);
}

TEST_CASE("CheckWhitespacesAreFiltered", "[shapes]")
{
    CHECK(!Shapes::recognize("  0  0  \n 0 \t 0", 2, 2).has_error());
}

TEST_CASE("SquareRecognitionTest", "[shapes]")
{
    const std::string input = R"(
        000000000000000
        000111111000000
        000111111000000
        000111111000000
        000111111000000
        000111111000000
        000111111000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
    )";

    CHECK_THAT(input, isRecognizedAs(Shapes::Square{ 3,1,6 }));
}

TEST_CASE("SquareRecognitionTest2", "[shapes]")
{
    const std::string input = R"(
        000000000000000
        000000000000000
        000000000000000
        000001111111000
        000001111111000
        000001111111000
        000001111111000
        000001111111000
        000001111111000
        000001111111000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
    )";

    CHECK_THAT(input, isRecognizedAs(Shapes::Square{ 5,3,7 }));
}

TEST_CASE("RotatedSquareRecognitionTest", "[shapes]")
{
    const std::string input = R"(
        000000000000000
        000000010000000
        000000111000000
        000001111100000
        000011111110000
        000001111100000
        000000111000000
        000000010000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
    )";

    CHECK_THAT(input, isRecognizedAs(Shapes::Square{ 4,4,6 }));
}

TEST_CASE("CircleRecognitionTest", "[shapes]")
{
    const std::string input = R"(
        000000000000000
        000000000000000
        000000000000000
        000001111000000
        000111111110000
        000111111110000
        001111111111000
        001111111111000
        001111111111000
        000111111110000
        000111111110000
        000001111000000
        000000000000000
        000000000000000
        000000000000000
    )";

    CHECK_THAT(input, isRecognizedAs(Shapes::Circle{ 7, 8, 4 }));
}

TEST_CASE("CircleRecognitionTest2", "[shapes]")
{
    const std::string input = R"(
        000000000000000
        000000111100000
        000011111111000
        000011111111000
        000111111111100
        000111111111100
        000111111111100
        000011111111000
        000011111111000
        000000111100000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
    )";

    CHECK_THAT(input, isRecognizedAs(Shapes::Circle{ 8, 6, 4 }));
}

TEST_CASE("NonSolidBodySquareRecognitionTest", "[shapes]")
{
    const std::string input = R"(
        000000000000000
        000111111000000
        000110011000000
        000111111000000
        000101111000000
        000111101000000
        000111111000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
    )";

    CHECK_THAT(input, isRecognizedAs(Shapes::Square{ 3,1,6 }));
}

TEST_CASE("NonSolidEdgesSquareRecognitionTest", "[shapes]")
{
    const std::string input = R"(
        000000000000000
        000011111000000
        000111111000000
        000111111000000
        000111111000000
        000111111000000
        000111111000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
        000000000000000
    )";

    CHECK_THAT(input, isRecognizedAs(Shapes::Square{ 3,1,6 }));
}

TEST_CASE("NonSolidBodyCircleRecognitionTest", "[shapes]")
{
    const std::string input = R"(
        000000000000000
        000000000000000
        000000000000000
        000001111000000
        000111111110000
        000101110110000
        001111111111000
        001110110011000
        001111111111000
        000111101110000
        000111111110000
        000001111000000
        000000000000000
        000000000000000
        000000000000000
    )";

    CHECK_THAT(input, isRecognizedAs(Shapes::Circle{ 7, 8, 4 }));
}

TEST_CASE("UnknownShapeRecognitionTest", "[shapes]")
{
    const std::string input = R"(
        000000000000000
        000000000000000
        001111100000000
        001111100000000
        001111100000000
        001111100000000
        001111100000000
        001111100000000
        001111100000000
        001111100000000
        001111100000000
        001111100000000
        001111100000000
        000000000000000
        000000000000000
    )";

    CHECK_THAT(input, isRecognizedAs(Shapes::Unknown{}));
}