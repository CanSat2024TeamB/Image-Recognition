#pragma once
#include <string>
#include <opencv2/opencv.hpp>

class cascade_handler {
private:
	cv::CascadeClassifier cascade;
public:
	std::vector<cv::Rect> apply(cv::Mat raw_img, double scale_factor = 1.1, int min_nerghbors = 3, cv::Size min_size = cv::Size());
	cv::CascadeClassifier get_cascade();
	void set_cascade(std::string path);
};