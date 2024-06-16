cmake_minimum_required(VERSION 3.4...3.18)
project(corvus_image)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)

pybind11_add_module(corvus_image src/header.h src/bind.h src/bind.cpp src/image.h src/image.cpp src/cascade_handler.h src/cascade_handler.cpp src/camera_handler.h src/camera_handler.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(corvus_image PRIVATE ${OpenCV_LIBRARIES})