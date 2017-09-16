#pragma once

#include "Shapes/circle.h"
#include "Shapes/square.h"
#include "outcome.hpp"

#include <boost/variant.hpp>

#include <string>
#include <tuple>

namespace outcome = OUTCOME_V2_NAMESPACE;
namespace Shapes {

enum class Error {
    InvalidDimensions,
    InvalidData
};

struct Unknown {
    bool operator==(const Unknown&) const { return true; }
};

using Shape = boost::variant<Circle, Square, Unknown>;
using RecognitionResult = outcome::result<Shape, Error>;

constexpr size_t DefaultDataWidth = 15;
constexpr size_t DefaultDataHeight = 15;
constexpr char DefaultDataDotChar = '1';
constexpr char DefaultDataEmptyChar = '0';

RecognitionResult recognize(const std::string& aChars,
    size_t aDataWidth = DefaultDataWidth,
    size_t aDataHeight = DefaultDataHeight,
    char aDot = DefaultDataDotChar,
    char aEmpty = DefaultDataEmptyChar);

std::string shapeToString(Shape aShape);
}
