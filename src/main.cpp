#include <chrono>
#include <iostream>
#include <filesystem>
#include "camera_handler.h"
#include "cascade_handler.h"
#include "image.h"


int main() {
	camera_handler camera;
	cascade_handler cascade("assets/haarcascade_frontalface_alt.xml");
	std::array<int, 2> prev_detect_pos;
	int prev_rect_width = 0;
	int prev_rect_height = 0;
	bool detected = false;
	int detect_width_margin = 50;
	int detect_height_margin = 50;

	std::array<int, 2> pos = { -1, -1 };

	while (true) {
		image img = camera.capture();

		//std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

		std::vector<cv::Rect> rects = {};
		if (!detected) {
			rects = cascade.get_rect(img);
		}
		else {
			rects = cascade.get_rect(img, prev_detect_pos, prev_rect_width + detect_width_margin, prev_rect_height + detect_height_margin);
		}
		
		if (rects.size() > 0) {
			prev_detect_pos = { rects[0].x + rects[0].width / 2, rects[0].y + rects[0].height / 2 };
			prev_rect_width = rects[0].width;
			prev_rect_height = rects[0].height;
			detected = true;
			img.draw_rect({ rects[0] });
		}
		else {
			detected = false;
		}

		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

		if (!detected) {
			std::vector<std::array<int, 2>> pos_list = cascade.get_target_coordinates(img);
			if (pos_list.size() > 0) {
				pos = pos_list[0];
			}
			else {
				pos = { -1, -1 };
			}
		}
		else {
			pos = cascade.get_target_coordinates_head(img, prev_detect_pos, prev_rect_width + detect_width_margin, prev_rect_height + detect_height_margin);
		}

		std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> elapsed_time = end - start;

		std::cout << "time: " << elapsed_time.count() << std::endl;
		std::cout << "pos: " << pos[0] << " " << pos[1] << std::endl;

		img.show();

		int key = cv::waitKey(1);
		if (key == 'q') {
			break;
		}
	}

	return 0;
}