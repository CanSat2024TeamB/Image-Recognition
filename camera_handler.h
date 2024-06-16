#pragma once
#include <opencv2/opencv.hpp>
#include "image.h"

class camera_handler {
private:
	int device_id;
	cv::VideoCapture camera;

public:
	camera_handler();
	camera_handler(int device_id);

	void set_camera(int device_id);

	int get_device_id();

	bool if_connected();
	cv::VideoCapture get_camera();
	image capture();
};