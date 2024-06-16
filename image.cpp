#include <opencv2/opencv.hpp>
#include <string>
#include "image.h"
#include "bind.h"

image::image() {}

image::image(std::string path) {
	read_image(path);
}

void image::read_image(std::string path) {
	img = cv::imread(path);
	return;
}

cv::Mat image::get_image() {
	return img;
}

void image::show(std::string window_name) {
	if (is_empty()) {
		return;
	}
	cv::imshow(window_name, img);
	return;
}

void image::show_until_any_input(std::string window_name, double key_wait_time) {
	show(window_name);
	cv::waitKey(key_wait_time);
	return;
}

bool image::is_empty() {
	return img.empty();
}

pybind11::array_t<uint8_t> image::to_numpy() {
	pybind11::array_t<uint8_t> result({ img.rows, img.cols, img.channels() });
	pybind11::buffer_info buffer = result.request();
	uint8_t* pointer = static_cast<uint8_t*>(buffer.ptr);

	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			for (int k = 0; k < img.channels(); ++k) {
				*pointer++ = img.at<cv::Vec3b>(i, j)[k];
			}
		}
	}

	return result;
}

// pybind
void bind_image(pybind11::module& m) {
	//pybind11::module m_image = m.def_submodule("image");

	pybind11::class_<image>(m, "image")
		.def(pybind11::init<>())
		.def(pybind11::init<std::string>())
		.def("read_image", &image::read_image, pybind11::arg("path"))
		.def("get_image", &image::get_image)
		.def("show_image", &image::show, pybind11::arg("window_name") = "")
		.def("show_image_until_any_input", &image::show_until_any_input, pybind11::arg("window_name") = "", pybind11::arg("key_wait_time") = 0)
		.def("is_empty", &image::is_empty)
		.def("to_numpy", &image::to_numpy);
}