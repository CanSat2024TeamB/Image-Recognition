#include "cascade_handler.h"
#include <opencv2/opencv.hpp>
#include <string>

std::vector<cv::Rect> cascade_handler::apply(cv::Mat raw_img, double scale_factor = 1.1, int min_nerghbors = 3, cv::Size min_size = cv::Size()) {
	cv::Mat gray_img;
	cv::cvtColor(raw_img, gray_img, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> custom_rect;
	cascade.detectMultiScale(gray_img, custom_rect, scale_factor, min_nerghbors, 0, min_size);

	return custom_rect;
}

cv::CascadeClassifier cascade_handler::get_cascade() {
	return this->cascade;
}

void cascade_handler::set_cascade(std::string path) {
	this->cascade.load(path);

	return;
}