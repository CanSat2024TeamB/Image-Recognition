#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "cascade_handler.h"

int main() {
	std::string cascade_path = "haarcascade_frontalface_alt.xml";
	std::string img_path = "face_sample.jpg";

	cascade_handler face_cascade(cascade_path);
	cv::Mat img = cv::imread(img_path);

	cv::Mat face = face_cascade.draw_rect(img);

	cv::imshow("face", face);
	cv::waitKey();

	return 0;
}