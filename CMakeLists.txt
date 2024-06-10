cmake_minimum_required(VERSION 3.4...3.18)
project(corvus-image)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)
pybind11_add_module(corvus-image header.h bind.h bind.cpp image.h image.cpp cascade_handler.h cascade_handler.cpp camera_handler.h camera_handler.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(corvus-image PRIVATE ${OpenCV_LIBRARIES})