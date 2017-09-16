#include "Shapes/shapes.h"

#include <boost/format.hpp>
#include <boost/functional/overloaded_function.hpp>
#include <boost/optional.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>

#include <opencv2/opencv.hpp>

#include <algorithm>

#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>

namespace {

std::string filterWhitespaces(const std::string& aData)
{
    return boost::copy_range<std::string>(aData | boost::adaptors::filtered([](const char c) { return !std::isspace(c); }));
}

bool checkDataCharsAreValid(const std::string& aData, const char aDot, const char aEmpty)
{
    return std::all_of(aData.cbegin(), aData.cend(), [=](const char c) { return c == aDot || c == aEmpty; });
}

boost::optional<Shapes::Error> validateData(const std::string& aData, const size_t aDataWidth, const size_t aDataHeight, const char aDot, const char aEmpty)
{
    if (aDot == aEmpty || !checkDataCharsAreValid(aData, aDot, aEmpty)) {
        return Shapes::Error::InvalidData;
    }

    if (aDataWidth == 0 || aDataHeight == 0 || aData.size() != aDataWidth * aDataHeight) {
        return Shapes::Error::InvalidDimensions;
    }

    return {};
}

template <typename T, boost::optional<T> (*recognize)(const cv::Mat&)>
boost::optional<Shapes::Shape> adaptRecognizer(const cv::Mat& mat)
{
    assert(recognize);
    auto result = recognize(mat);
    if (result) {
        return *result;
    }
    return {};
}

Shapes::Shape recognizeMat(const cv::Mat& aMat)
{
    using Recognizer = boost::optional<Shapes::Shape> (*)(const cv::Mat&);
    const Recognizer recognizers[] = { adaptRecognizer<Shapes::Square, Shapes::recognizeSquare>,
        adaptRecognizer<Shapes::Circle, Shapes::recognizeCircle> };

    for (const auto& recognize : recognizers) {
        const auto result = recognize(aMat);
        if (result) {
            return *result;
        }
    }

    return Shapes::Unknown{};
}
}

namespace Shapes {

RecognitionResult recognize(const std::string& aChars, const size_t aDataWidth, const size_t aDataHeight, const char aDot, const char aEmpty)
{
    const auto filteredChars = filterWhitespaces(aChars);
    const auto error = validateData(filteredChars, aDataWidth, aDataHeight, aDot, aEmpty);
    if (error) {
        return *error;
    }

    auto bytes = boost::copy_range<std::vector<unsigned char>>(filteredChars | boost::adaptors::transformed([=](const char c) -> unsigned char {
        assert(c == aDot || c == aEmpty);
        return c == aDot ? 255 : 0;
    }));

    assert(bytes.size() == aDataWidth * aDataHeight);
    cv::Mat cvMat(aDataWidth, aDataHeight, CV_8UC1, bytes.data());
    return recognizeMat(cvMat);
}

std::string shapeToString(Shapes::Shape aShape)
{
    auto visitor = boost::make_overloaded_function(
        [](const Shapes::Square& square) { return (boost::format("square with left: %1% top: %2% side %3%") % square.left % square.top % square.side).str(); },
        [](const Shapes::Circle& circle) { return (boost::format("circle with x: %1% y: %2% radius: %3%") % circle.x % circle.y % circle.radius).str(); },
        [](const Shapes::Unknown&) { return std::string("unknown shape"); });

    return boost::apply_visitor(visitor, aShape);
}
}
