#pragma once
#include <string>
#include <map>
#include <opencv2/opencv.hpp>
#include "image.h"

class cascade_handler {
private:
	cv::CascadeClassifier cascade;

public:
	cascade_handler(std::string path);

	void set_cascade(std::string path);

	cv::CascadeClassifier get_cascade();

	std::vector<std::map<std::string, int>> get_rect(image raw_img, double scale_factor = 1.1, int min_neighbors = 3, int min_size_width = 20, int min_size_height = 20);
	std::vector<std::map<std::string, int>> get_rect(image raw_img, std::array<int, 2> detect_center, int detect_width, int detect_height, double scale_factor = 1.1, int min_neighbors = 3, int min_size_width = 20, int min_size_height = 20);
	std::vector<std::array<int, 2>> get_target_coordinates(image raw_img, double scale_factor = 1.1, int min_neighbors = 3, int min_size_width = 20, int min_size_height = 20);
	std::vector<std::array<int, 2>> get_target_coordinates(image raw_img, std::array<int, 2> detect_center, int detect_width, int detect_height, double scale_factor = 1.1, int min_neighbors = 3, int min_size_width = 20, int min_size_height = 20);
	std::array<int, 2> get_target_coordinates_head(image raw_img, std::array<int, 2> detect_center, int detect_width, int detect_height, double scale_factor = 1.1, int min_neighbors = 3, int min_size_width = 20, int min_size_height = 20);
	double measure_prediction_time(image test_img);
};