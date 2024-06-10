#include "camera_handler.h"
#include "bind.h"

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

//pybind
void bind_camera_handler(pybind11::module& m) {
	pybind11::module m_camera_handler = m.def_submodule("camera_handler");

	pybind11::class_<camera_handler>(m_camera_handler, "camera_handler")
		.def(pybind11::init<>())
		.def(pybind11::init<int>())
		.def("set_camera", &camera_handler::set_camera, pybind11::arg("device_id"))
		.def("get_device_id", &camera_handler::get_device_id)
		.def("if_connected", &camera_handler::if_connected)
		.def("get_camera", &camera_handler::get_camera)
		.def("capture", &camera_handler::capture);
}