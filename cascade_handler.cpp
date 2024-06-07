#include <opencv2/opencv.hpp>
#include <string>
#include "cascade_handler.h"

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

std::vector<cv::Rect> cascade_handler::get_rect(cv::Mat raw_img, double scale_factor, int min_neighbors, cv::Size min_size) {
	cv::Mat gray_img;
	cv::cvtColor(raw_img, gray_img, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> rects;
	cascade.detectMultiScale(gray_img, rects, scale_factor, min_neighbors, 0, min_size);

	return rects;
}

cv::Mat cascade_handler::draw_rect(cv::Mat raw_img, double scale_factor, int min_neighbors, cv::Size min_size) {
	cv::Mat dst_img = raw_img.clone();

	std::vector<cv::Rect> rects = get_rect(raw_img, scale_factor, min_neighbors, min_size);
	for (cv::Rect rect : rects) {
		cv::rectangle(dst_img, rect, cv::Scalar(255, 0, 0));
	}

	return dst_img;
}