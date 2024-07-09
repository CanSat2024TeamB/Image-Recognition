#pragma once
#include <opencv2/opencv.hpp>
#include <pybind11/numpy.h>
#include <string>

class image {
private:
	cv::Mat img;

public:
	image();
	image(cv::Mat img);
	image(std::string path);

	void set_image(cv::Mat img);
	void read_image(std::string image);

	cv::Mat get_image();

	void show(std::string window_name = "");
	void show_until_any_input(std::string window_name = "", double key_wait_time = 0);
	void draw_rect(std::vector<cv::Rect> rects);
	void save(std::string path);
	bool is_empty();
	int width();
	int height();
	pybind11::array_t<uint8_t> to_numpy();
};