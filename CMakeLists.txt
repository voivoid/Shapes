cmake_minimum_required(VERSION 3.9)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.44.tar.gz"
    SHA1 "c4cfcc0cd39fdae8de08f6205b7f34cab4a7ba79"
)

project(ShapeRecognition)

hunter_add_package(OpenCV)
find_package(OpenCV REQUIRED)

hunter_add_package(Boost)
find_package(Boost REQUIRED)

hunter_add_package(Catch)
find_package(Catch2 REQUIRED)

set(CMAKE_CXX_STANDARD 14)


add_library(ShapeLib src/shapes.cpp
                     src/square.cpp
                     inc/Shapes/square.h
                     src/circle.cpp
                     inc/Shapes/circle.h
                     inc/Shapes/shapes.h)


target_include_directories(ShapeLib PUBLIC inc thirdparty)

if (MSVC)
    target_compile_options(ShapeLib PUBLIC /W4 /WX)
else()
    target_compile_options(ShapeLib PUBLIC -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(ShapeLib PRIVATE ${OpenCV_LIBS} PUBLIC Boost::boost)

add_executable(ShapeApp app/main.cpp)
target_link_libraries(ShapeApp PRIVATE ShapeLib)


enable_testing()
add_executable(ShapeTests tests/main.cpp
                          tests/shapes.cpp
                          tests/matchers.h
                          tests/matchers.cpp)
target_link_libraries(ShapeTests PRIVATE ShapeLib Catch2::Catch)
target_include_directories(ShapeTests PRIVATE src)

add_test(ShapeTests ShapeTests)
