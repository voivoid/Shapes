#pragma once

#include <boost/optional.hpp>

namespace cv {
class Mat;
}

namespace Shapes {

struct Circle {
    const long x;
    const long y;
    const size_t radius;

    bool operator==(const Circle& rhs) const
    {
        return x == rhs.x && y == rhs.y && radius == rhs.radius;
    }
};

boost::optional<Circle> recognizeCircle(const cv::Mat& aMat);
}