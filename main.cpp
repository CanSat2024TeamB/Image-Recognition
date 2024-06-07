#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "cascade_handler.h"

int main() {
	std::string cascade_path = "";
	std::string img_path = "";

	cascade_handler face_cascade(cascade_path);
	cv::Mat img = cv::imread(img_path);

	face_cascade.draw_rect(img);

	cv::imshow("face", img);
	cv::waitKey();

	return 0;
}