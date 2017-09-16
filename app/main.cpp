#include "Shapes/shapes.h"

#include <iostream>
#include <iterator>
#include <string>

namespace {

void handleError(const Shapes::Error error)
{
    switch (error) {
    case Shapes::Error::InvalidData:
        std::cerr << "Invalid data\n";
        break;
    case Shapes::Error::InvalidDimensions:
        std::cerr << "Invalid data dimensions\n";
        break;
    }
}

int safe_main()
{
    std::istream_iterator<char> it(std::cin);
    std::istream_iterator<char> end;
    std::string input(it, end);

    auto result = Shapes::recognize(input);
    if (result.has_error()) {
        handleError(result.error());
        return 1;
    }

    std::cout << Shapes::shapeToString(result.value()) << "\n";

    return 0;
}
}

int main()
{
    int result = -1;
    try {
        result = safe_main();
    } catch (const std::exception& ex) {
        std::cerr << "Unhandled exception: " << ex.what() << "\n";
    } catch (...) {
        std::cerr << "Unhandled exception: unknown\n";
    }

    return result;
}