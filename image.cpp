#include <opencv2/opencv.hpp>
#include <string>
#include "image.h"

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

void image::show_image_until_any_input(std::string window_name, double wait_time) {
	show_image(window_name);
	cv::waitKey(wait_time);
	return;
}

bool image::is_empty() {
	return img.empty();
}