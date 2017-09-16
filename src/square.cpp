#include "Shapes/square.h"

#include <vector>

#include <opencv2/opencv.hpp>

#include <cassert>

namespace {

double getRectangleSide(const cv::Point& p1, const cv::Point& p2)
{
    cv::Point diff = p1 - p2;
    if (diff.x) {
        diff.x = std::abs(diff.x) + 1;
    }
    if (diff.y) {
        diff.y = std::abs(diff.y) + 1;
    }
    return cv::sqrt(diff.x * diff.x + diff.y * diff.y);
}

std::vector<double> getRectangleSides(const std::vector<cv::Point>& contour)
{
    assert(contour.size() == 4);
    return { getRectangleSide(contour[0], contour[1]),
        getRectangleSide(contour[1], contour[2]),
        getRectangleSide(contour[2], contour[3]),
        getRectangleSide(contour[3], contour[0]) };
}

bool checkAllSidesAreSame(const std::vector<double>& sides)
{
    assert(!sides.empty());
    const auto side = sides.front();
    return std::all_of(sides.cbegin(), sides.cend(), [side](const double s) { return std::abs(s - side) <= std::numeric_limits<double>::epsilon(); });
}

cv::Point getLeftTopPoint(const std::vector<cv::Point>& contour)
{
    return *std::min_element(contour.cbegin(), contour.cend(), [](const cv::Point p1, const cv::Point p2) { return std::tie(p1.x, p1.y) < std::tie(p2.x, p2.y); });
}
}

namespace Shapes {

boost::optional<Square> recognizeSquare(const cv::Mat& aMat)
{
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(aMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    if (contours.size() != 1) {
        return {};
    }

    const auto& contour = contours.front();
    if (contour.size() != 4) {
        return {};
    }

    const auto sides = getRectangleSides(contour);
    if (!checkAllSidesAreSame(sides)) {
        return {};
    }

    const auto leftTop = getLeftTopPoint(contour);

    assert(!sides.empty());
    return Shapes::Square{ leftTop.x, leftTop.y, static_cast<size_t>(std::llround(sides.front())) };
}
}