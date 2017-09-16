#pragma once

#include "Shapes/shapes.h"
#include "catch.hpp"

#include <string>

class ShapeMatcher : public Catch::MatcherBase<std::string> {
public:
    ShapeMatcher(Shapes::Shape aShape);

    virtual bool match(const std::string& aData) const override;
    virtual std::string describe() const override;

private:
    const Shapes::Shape iShape;
};

ShapeMatcher isRecognizedAs(Shapes::Shape aShape);