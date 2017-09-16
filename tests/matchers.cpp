#include "matchers.h"

ShapeMatcher::ShapeMatcher(Shapes::Shape aShape)
    : iShape(aShape)
{
}

bool ShapeMatcher::match(const std::string& aData) const
{
    const auto result = Shapes::recognize(aData);
    return result.has_value() && result.value() == iShape;
}

std::string ShapeMatcher::describe() const
{
    return std::string("is not recognized as ") + Shapes::shapeToString(iShape);
}

ShapeMatcher isRecognizedAs(Shapes::Shape aShape)
{
    return ShapeMatcher(aShape);
}
