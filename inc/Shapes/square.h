#pragma once

#include <boost/optional.hpp>

namespace cv {
class Mat;
}

namespace Shapes {

struct Square {
    const long left;
    const long top;
    const size_t side;

    bool operator==(const Square& rhs) const
    {
        return left == rhs.left && top == rhs.top && side == rhs.side;
    }
};

boost::optional<Square> recognizeSquare(const cv::Mat& aMat);
}