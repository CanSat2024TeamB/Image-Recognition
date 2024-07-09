#pragma once
#include <opencv2/opencv.hpp>
#include "image.h"

class camera_handler {
private:
	int device_id;
	int width;
	int height;
	cv::VideoCapture camera;

	void get_resolution();

public:
	camera_handler();
	camera_handler(int device_id);

	void set_camera(int device_id);

	int get_device_id();
	int get_width();
	int get_height();
	bool if_connected();
	cv::VideoCapture get_camera();
	image capture();
	std::array<float, 2> normalize_position(std::array<int, 2> position);
};