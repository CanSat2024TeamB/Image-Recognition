#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat convert_to_grayscale(cv::Mat src_img) {
	cv::Mat dst_img;
	cv::cvtColor(src_img, dst_img, cv::COLOR_BGR2GRAY);

	return dst_img;
}

int main() {
	cv::Mat img = cv::imread("sample.png");
	if (img.empty()) {
		return -1;
	}

	cv::Mat img_canny;
	cv::Mat img_bin;

	img_bin = convert_to_grayscale(img);
	cv::Canny(img, img_canny, 500, 700);

	std::vector<cv::Vec2f> lines;

	cv::HoughLines(img_canny, lines, 0.5, CV_PI / 360, 80);

	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it) {
		float rho = (*it)[0];
		float theta = (*it)[1];
		cv::Point pt1;
		cv::Point pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;

		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * a);
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * a);

		cv::line(img, pt1, pt2, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
	}

	cv::imshow("img", img);

	cv::waitKey(0);

	//std::cout << "img: " << img.channels() << " channels" << std::endl;
	//std::cout << "img_bin: " << img_bin.channels() << " channels" << std::endl;

	return 0;
}