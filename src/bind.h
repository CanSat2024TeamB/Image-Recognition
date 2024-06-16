#pragma once
#include <pybind11/pybind11.h>

void bind_image(pybind11::module& m);
void bind_cascade_handler(pybind11::module& m);
void bind_camera_handler(pybind11::module& m);