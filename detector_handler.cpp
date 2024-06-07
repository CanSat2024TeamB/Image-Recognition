#include <dlib/image_processing/frontal_face_detector.h>
#include "detector_handler.h"

detector_handler::detector_handler() : detector(dlib::get_frontal_face_detector()) {}

std::vector<dlib::rectangle> detector_handler::get_rect(cv::Mat raw_img, double scale_factor, int min_neighbors, cv::Size min_size) {
	cv::Mat gray_img;
	cv::cvtColor(raw_img, gray_img, cv::COLOR_BGR2GRAY);

	std::vector<dlib::rectangle> rects = detector(gray_img);

	return rects;
}

cv::Mat detector_handler::draw_rect(cv::Mat raw_img, double scale_factor, int min_neighbors, cv::Size min_size) {
	cv::Mat dst_img = raw_img.clone();

	std::vector<dlib::rectangle> rects = get_rect(raw_img, scale_factor, min_neighbors, min_size);
	for (dlib::rectangle rect : rects) {
		cv::rectangle(dst_img, cv::Point(rect.tl_corner().x(), rect.tl_corner().y()), cv::Point(rect.br_corner().x(), rect.br_corner().y()), cv::Scalar(255, 0, 0));
	}

	return dst_img;
}