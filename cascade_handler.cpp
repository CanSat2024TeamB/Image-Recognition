#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>
#include "cascade_handler.h"
#include "bind.h"

cascade_handler::cascade_handler(std::string path) {
	set_cascade(path);
}

void cascade_handler::set_cascade(std::string path) {
	cascade.load(path);

	return;
}

cv::CascadeClassifier cascade_handler::get_cascade() {
	return cascade;
}

std::vector<cv::Rect> cascade_handler::get_rect(cv::Mat raw_img, double scale_factor, int min_neighbors, int min_size_width, int min_size_height) {
	cv::Mat gray_img;
	cv::cvtColor(raw_img, gray_img, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> rects;
	cv::Size min_size = cv::Size(min_size_width, min_size_height);
	cascade.detectMultiScale(gray_img, rects, scale_factor, min_neighbors, 0, min_size);

	return rects;
}

cv::Mat cascade_handler::draw_rect(cv::Mat raw_img, double scale_factor, int min_neighbors, int min_size_width, int min_size_height) {
	cv::Mat dst_img = raw_img.clone();

	std::vector<cv::Rect> rects = get_rect(raw_img, scale_factor, min_neighbors, min_size_width, min_size_height);
	for (cv::Rect rect : rects) {
		cv::rectangle(dst_img, rect, cv::Scalar(255, 0, 0));
	}

	return dst_img;
}

double cascade_handler::measure_prediction_time(cv::Mat test_img) {
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	draw_rect(test_img);

	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> elapsed_time = end - start;
	
	return elapsed_time.count();
}

//pybind
void bind_cascade_handler(pybind11::module& m) {
	//pybind11::module m_cascade_handler = m.def_submodule("cascade_handler");

	pybind11::class_<cascade_handler>(m, "cascade_handler")
		.def(pybind11::init<std::string>())
		.def("set_cascade", &cascade_handler::set_cascade, pybind11::arg("path"))
		.def("get_cascade", &cascade_handler::get_cascade)
		.def("get_rect", &cascade_handler::get_rect, pybind11::arg("raw_img"), pybind11::arg("scale_factor") = 1.1, pybind11::arg("min_neighbors") = 3, pybind11::arg("min_size_width") = 20, pybind11::arg("min_size_height") = 20)
		.def("draw_rect", &cascade_handler::draw_rect, pybind11::arg("raw_img"), pybind11::arg("scale_factor") = 1.1, pybind11::arg("min_neighbors") = 3, pybind11::arg("min_size_width") = 20, pybind11::arg("min_size_height") = 20)
		.def("mesure_prediction_time", &cascade_handler::measure_prediction_time, pybind11::arg("test_img"));
}