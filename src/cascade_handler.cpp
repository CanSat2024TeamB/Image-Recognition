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

std::vector<cv::Rect> cascade_handler::get_rect(image raw_img, double scale_factor, int min_neighbors, int min_size_width, int min_size_height) {
	//cv::Mat gray_img;
	//cv::cvtColor(raw_img.get_image(), gray_img, cv::COLOR_BGR2GRAY);
	cv::Mat gray_img = raw_img.get_image();

	std::vector<cv::Rect> rects;
	cv::Size min_size = cv::Size(min_size_width, min_size_height);
	cascade.detectMultiScale(gray_img, rects, scale_factor, min_neighbors, 0, min_size);

	return rects;
}

std::vector<cv::Rect> cascade_handler::get_rect(image raw_img, std::array<int, 2> detect_center, int detect_width, int detect_height, double scale_factor, int min_neighbors, int min_size_width, int min_size_height) {
	cv::Rect detect_range(cv::Point(detect_center[0] - detect_width / 2, detect_center[1] - detect_height / 2), cv::Point(detect_center[0] + detect_width / 2, detect_center[1] + detect_height / 2));
	if (detect_range.x < 0) {
		detect_range.x = 0;
	}
	if (detect_range.x + detect_range.width > raw_img.width()) {
		detect_range.width = raw_img.width() - detect_range.x;
	}
	if (detect_range.y < 0) {
		detect_range.y = 0;
	}
	if(detect_range.y + detect_range.height > raw_img.height()) {
		detect_range.height = raw_img.height() - detect_range.y;
	}
	cv::Mat detect_img = raw_img.get_image()(detect_range);
	
	std::vector<cv::Rect> rects = get_rect(detect_img, scale_factor, min_neighbors, min_size_width, min_size_height);
	std::vector<cv::Rect> results = {};
	for (cv::Rect rect : rects) {
		int x = rect.x + detect_center[0] - detect_width / 2;
		int y = rect.y + detect_center[1] - detect_height / 2;
		results.push_back(cv::Rect(x, y, rect.width, rect.height));
	}

	return results;
}

std::vector<std::array<int, 2>> cascade_handler::get_target_coordinates(image raw_img, double scale_factor, int min_neighbors, int min_size_width, int min_size_height) {
	std::vector<cv::Rect> rects = get_rect(raw_img, scale_factor, min_neighbors, min_size_width, min_size_height);

	std::vector<std::array<int, 2>> coordinates = {};
	for (cv::Rect rect : rects) {
		coordinates.push_back({ rect.x + rect.width / 2, rect.y + rect.height / 2 });
	}

	return coordinates;
}

std::vector<std::array<int, 2>> cascade_handler::get_target_coordinates(image raw_img, std::array<int, 2> detect_center, int detect_width, int detect_height, double scale_factor, int min_neighbors, int min_size_width, int min_size_height) {
	std::vector<cv::Rect> rects = get_rect(raw_img, detect_center, detect_width, detect_height, scale_factor, min_neighbors, min_size_width, min_size_height);

	std::vector<std::array<int, 2>> coordinates = {};
	for (cv::Rect rect : rects) {
		coordinates.push_back({ rect.x + rect.width / 2, rect.y + rect.height / 2 });
	}

	return coordinates;
}

std::array<int, 2> cascade_handler::get_target_coordinates_head(image raw_img, std::array<int, 2> detect_center, int detect_width, int detect_height, double scale_factor, int min_neighbors, int min_size_width, int min_size_height) {
	std::vector<cv::Rect> rects = get_rect(raw_img, detect_center, detect_width, detect_height, scale_factor, min_neighbors, min_size_width, min_size_height);

	if (rects.size() > 0) {
		return { rects[0].x + rects[0].width / 2, rects[0].y + rects[0].height / 2 };
	}
	else {
		return { -1, -1 };
	}
}

double cascade_handler::measure_prediction_time(image test_img) {
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	std::vector<cv::Rect> rects = get_rect(test_img);

	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> elapsed_time = end - start;
	
	return elapsed_time.count();
}

//pybind
void bind_cascade_handler(pybind11::module& m) {
	pybind11::class_<cascade_handler>(m, "cascade_handler")
		.def(pybind11::init<std::string>())
		.def("set_cascade", &cascade_handler::set_cascade, pybind11::arg("path"))
		.def("get_cascade", &cascade_handler::get_cascade)
		.def("get_rect", pybind11::overload_cast<image, double, int, int, int>(&cascade_handler::get_rect), pybind11::arg("raw_img"), pybind11::arg("scale_factor") = 1.1, pybind11::arg("min_neighbors") = 3, pybind11::arg("min_size_width") = 20, pybind11::arg("min_size_height") = 20)
		.def("get_rect", pybind11::overload_cast<image, std::array<int, 2>, int, int, double, int, int, int>(&cascade_handler::get_rect), pybind11::arg("raw_img"), pybind11::arg("detect_center"), pybind11::arg("detect_width"), pybind11::arg("detect_height"), pybind11::arg("scale_factor") = 1.1, pybind11::arg("min_neighbors") = 3, pybind11::arg("min_size_width") = 20, pybind11::arg("min_size_height") = 20)
		.def("get_target_coordinates", pybind11::overload_cast<image, double, int, int, int>(&cascade_handler::get_target_coordinates), pybind11::arg("raw_img"), pybind11::arg("scale_factor") = 1.1, pybind11::arg("min_neighbors") = 3, pybind11::arg("min_size_width") = 20, pybind11::arg("min_size_height") = 20)
		.def("get_target_coordinates", pybind11::overload_cast<image, std::array<int, 2>, int, int, double, int, int, int>(&cascade_handler::get_target_coordinates), pybind11::arg("raw_img"), pybind11::arg("detect_center"), pybind11::arg("detect_width"), pybind11::arg("detect_height"), pybind11::arg("scale_factor") = 1.1, pybind11::arg("min_neighbors") = 3, pybind11::arg("min_size_width") = 20, pybind11::arg("min_size_height") = 20)
		.def("get_target_coordinates_head", &cascade_handler::get_target_coordinates_head, pybind11::arg("raw_img"), pybind11::arg("detect_center"), pybind11::arg("detect_width"), pybind11::arg("detect_height"), pybind11::arg("scale_factor") = 1.1, pybind11::arg("min_neighbors") = 3, pybind11::arg("min_size_width") = 20, pybind11::arg("min_size_height") = 20)
		.def("mesure_prediction_time", &cascade_handler::measure_prediction_time, pybind11::arg("test_img"));
}