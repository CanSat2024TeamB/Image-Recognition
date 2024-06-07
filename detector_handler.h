#pragma once
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>

class detector_handler {
private:
	dlib::frontal_face_detector detector;

public:
	detector_handler();

	std::vector<dlib::rectangle> get_rect(cv::Mat raw_img, double scale_factor = 1.1, int min_neighbors = 3, cv::Size min_size = cv::Size(20, 20));
	cv::Mat draw_rect(cv::Mat raw_img, double scale_factor = 1.1, int min_neighbors = 3, cv::Size min_size = cv::Size(20, 20));
};
