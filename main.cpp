#include <iostream>
#include <string>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "cascade_handler.h"

int main() {
	std::string cascade_path = "haarcascade_frontalface_alt.xml";
	std::string img_path = "face_sample2.jpg";

	cascade_handler face_cascade(cascade_path);
	cv::Mat img = cv::imread(img_path);

	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	cv::Mat face = face_cascade.draw_rect(img);

	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

	std::chrono::duration<double, std::milli> elapsed = end - start;

	std::cout << elapsed.count() << " ms" << std::endl;

	cv::imshow("face", face);
	cv::waitKey();

	return 0;
}