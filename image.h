#pragma once
#include <opencv2/opencv.hpp>
#include <pybind11/numpy.h>
#include <string>

class image {
private:
	cv::Mat img;
public:
	image();
	image(std::string path);

	void read_image(std::string image);

	cv::Mat get_image();

	void show(std::string window_name = "");
	void show_until_any_input(std::string window_name = "", double key_wait_time = 0);
	bool is_empty();
	pybind11::array_t<uint8_t> to_numpy();
};