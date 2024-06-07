#pragma once
#include <string>
#include <opencv2/opencv.hpp>

class cascade_handler {
private:
	cv::CascadeClassifier cascade;

public:
	cascade_handler(std::string path);

	void set_cascade(std::string path);

	cv::CascadeClassifier get_cascade();

	std::vector<cv::Rect> get_rect(cv::Mat raw_img, double scale_factor = 1.1, int min_neighbors = 3, cv::Size min_size = cv::Size());
	cv::Mat draw_rect(cv::Mat raw_img, double scale_factor = 1.1, int min_neighbors = 3, cv::Size min_size = cv::Size());
};