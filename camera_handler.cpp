#include "camera_handler.h"

camera_handler::camera_handler() : camera_handler(0) {}

camera_handler::camera_handler(int device_id) {
	set_camera(device_id);
}

void camera_handler::set_camera(int device_id) {
	this->device_id = device_id;
	camera.open(device_id);
}

int camera_handler::get_device_id() {
	return device_id;
}

bool camera_handler::if_connected() {
	return camera.isOpened();
}

cv::VideoCapture camera_handler::get_camera() {
	return camera;
}

cv::Mat camera_handler::capture() {
	cv::Mat frame;
	if (!camera.isOpened()) {
		return frame;
	}

	camera.read(frame);

	return frame;
}