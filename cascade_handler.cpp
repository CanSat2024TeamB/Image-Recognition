#include "cascade_handler.h"
#include <opencv2/opencv.hpp>
#include <string>

cascade_handler::cascade_handler(std::string path) {
	set_cascade(path);
}

void cascade_handler::set_cascade(std::string path) {
	cascade.load(path);

	return;
}

cv::CascadeClassifier cascade_handler::get_cascade() {
	return this->cascade;
}

std::vector<cv::Rect> cascade_handler::get_rect(cv::Mat raw_img, double scale_factor = 1.1, int min_neighbors = 3, cv::Size min_size = cv::Size()) {
	cv::Mat gray_img;
	cv::cvtColor(raw_img, gray_img, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> custom_rect;
	cascade.detectMultiScale(gray_img, custom_rect, scale_factor, min_neighbors, 0, min_size);

	return custom_rect;
}

cv::Mat cascade_handler::draw_rect(cv::Mat raw_img, double scale_factor = 1.1, int min_neighbors = 3, cv::Size min_size = cv::Size()) {
	cv::Mat dst_img = raw_img.clone();

	std::vector<cv::Rect> rects = get_rect(raw_img, scale_factor, min_neighbors, min_size);
	for (cv::Rect rect : rects) {
		cv::rectangle(dst_img, rect, cv::Scalar(255, 0, 0), 3);
	}

	return dst_img;
}