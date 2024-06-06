#pragma once
#include <string>
#include <opencv2/opencv.hpp>

class CascadeHandler {
private:
	cv::CascadeClassifier cascade;
public:
	std::vector<cv::Rect> apply(cv::Mat, double, int, cv::Size);

	cv::CascadeClassifier get_cascade();

	void set_cascade(std::string);
};