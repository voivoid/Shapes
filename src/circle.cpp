#include "Shapes/circle.h"

#include <vector>

#include <opencv2/opencv.hpp>

namespace Shapes {

boost::optional<Circle> recognizeCircle(const cv::Mat& aMat)
{
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(aMat, circles, CV_HOUGH_GRADIENT, 1, 15, 15, 10, 0, 15);

    if (!circles.empty()) {
        const auto& circle = circles.front();
        const auto x = std::lround(circle[0]);
        const auto y = std::lround(circle[1]);
        const auto radius = std::lround(circle[2]);

        assert(radius >= 0);
        return Shapes::Circle{ x, y, static_cast<size_t>(radius) };
    }

    return {};
}
}