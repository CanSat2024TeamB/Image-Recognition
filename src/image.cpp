#include "image.h"
#include "bind.h"

image::image() {}

image::image(cv::Mat img) {
	set_image(img);
}

image::image(std::string path) {
	read_image(path);
}

void image::set_image(cv::Mat img) {
	this->img = img;
	return;
}

void image::read_image(std::string path) {
	img = cv::imread(path);
	return;
}

cv::Mat image::get_image() {
	return img;
}

void image::show(std::string window_name) {
	if (is_empty()) {
		return;
	}
	cv::imshow(window_name, img);
	return;
}

void image::show_until_any_input(std::string window_name, double key_wait_time) {
	show(window_name);
	cv::waitKey(key_wait_time);
	return;
}

void image::draw_rect(std::vector<cv::Rect> rects) {
	for (cv::Rect rect : rects) {
		cv::rectangle(img, rect, cv::Scalar(255, 0, 0));
	}
	return;
}

void image::save(std::string path) {
	if (!is_empty) {
		cv::imwrite(path, img);
	}
}

bool image::is_empty() {
	return img.empty();
}

int image::width() {
	return img.cols;
}

int image::height() {
	return img.rows;
}

pybind11::array_t<uint8_t> image::to_numpy() {
	pybind11::array_t<uint8_t> result({ img.rows, img.cols, img.channels() });
	pybind11::buffer_info buffer = result.request();
	uint8_t* pointer = static_cast<uint8_t*>(buffer.ptr);

	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			for (int k = 0; k < img.channels(); ++k) {
				*pointer++ = img.at<cv::Vec3b>(i, j)[k];
			}
		}
	}

	return result;
}

// pybind
void bind_image(pybind11::module& m) {
	pybind11::class_<image>(m, "image")
		.def(pybind11::init<>())
		.def(pybind11::init<std::string>())
		.def("read_image", &image::read_image, pybind11::arg("path"))
		.def("get_image", &image::get_image)
		.def("draw_rect", &image::draw_rect, pybind11::arg("rects"))
		.def("save", &image::save, pybind11::arg("path"))
		.def("is_empty", &image::is_empty)
		.def("width", &image::width)
		.def("hwight", &image::height)
		.def("to_numpy", &image::to_numpy);
}