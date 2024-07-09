#include "camera_handler.h"
#include "bind.h"

camera_handler::camera_handler() : camera_handler(0) {}

camera_handler::camera_handler(int device_id) {
	set_camera(device_id);
	width = 0;
	height = 0;

	get_resolution();
}

void camera_handler::get_resolution() {
	if (!if_connected()) {
		return;
	}

	image test = capture();
	width = test.width();
	height = test.height();
}

void camera_handler::set_camera(int device_id) {
	this->device_id = device_id;
	camera.open(device_id);

	get_resolution();
}

int camera_handler::get_device_id() {
	return device_id;
}

int camera_handler::get_width() {
	return width;
}

int camera_handler::get_height() {
	return height;
}

bool camera_handler::if_connected() {
	return camera.isOpened();
}

cv::VideoCapture camera_handler::get_camera() {
	return camera;
}

image camera_handler::capture() {
	cv::Mat frame;
	if (!if_connected()) {
		return frame;
	}

	camera.read(frame);

	return image(frame);
}

std::array<float, 2> camera_handler::normalize_position(std::array<int, 2> position) {
	if (get_width() == 0 || get_height() == 0) {
		return { (float)position[0], (float)position[1] };
	}
	else {
		return { (float)((float)position[0] / get_width() - 0.5), (float)((float)position[1] / get_height() - 0.5) };
	}
}

//pybind
void bind_camera_handler(pybind11::module& m) {
	pybind11::class_<camera_handler>(m, "camera_handler")
		.def(pybind11::init<>())
		.def(pybind11::init<int>())
		.def("set_camera", &camera_handler::set_camera, pybind11::arg("device_id"))
		.def("get_device_id", &camera_handler::get_device_id)
		.def("get_width", &camera_handler::get_width)
		.def("get_height", &camera_handler::get_height)
		.def("if_connected", &camera_handler::if_connected)
		.def("capture", &camera_handler::capture)
		.def("normalize_position", &camera_handler::normalize_position, pybind11::arg("position"));
}