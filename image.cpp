#include <opencv2/opencv.hpp>
#include <string>
#include "image.h"
#include "bind.h"

image::image() {}

image::image(std::string path) {
	read_image(path);
}

void image::read_image(std::string path) {
	cv::imread(path);
	return;
}

cv::Mat image::get_image() {
	return img;
}

void image::show_image(std::string window_name) {
	if (is_empty()) {
		return;
	}
	cv::imshow(window_name, img);
	return;
}

void image::show_image_until_any_input(std::string window_name, double key_wait_time) {
	show_image(window_name);
	cv::waitKey(key_wait_time);
	return;
}

bool image::is_empty() {
	return img.empty();
}

// pybind
void bind_image(pybind11::module& m) {
	pybind11::module m_image = m.def_submodule("image");

	pybind11::class_<image>(m_image, "image")
		.def(pybind11::init<>())
		.def(pybind11::init<std::string>())
		.def("read_image", &image::read_image, pybind11::arg("path"))
		.def("get_image", &image::get_image)
		.def("show_image", &image::show_image, pybind11::arg("window_name") = "")
		.def("show_image_until_any_input", &image::show_image_until_any_input, pybind11::arg("window_name") = "", pybind11::arg("key_wait_time") = 0)
		.def("is_empty", &image::is_empty);
}