#include "rect.h"

std::map<std::string, int> convert_to_map(cv::Rect rect) {
	std::map<std::string, int> rect_map;
	rect_map["x"] = rect.x;
	rect_map["y"] = rect.y;
	rect_map["width"] = rect.width;
	rect_map["height"] = rect.height;
	return rect_map;
}

std::vector<std::map<std::string, int>> convert_to_maps(std::vector<cv::Rect> rects) {
	std::vector<std::map<std::string, int>> rect_maps;
	for (cv::Rect rect : rects) {
		rect_maps.push_back(convert_to_map(rect));
	}
	return rect_maps;
}

cv::Rect convert_to_rect(std::map<std::string, int> map) {
	return cv::Rect(map["x"], map["y"], map["width"], map["height"]);
}

std::vector<cv::Rect> convert_to_rects(std::vector<std::map<std::string, int>> maps) {
	std::vector<cv::Rect> rects;
	for (std::map<std::string, int> map : maps) {
		rects.push_back(convert_to_rect(map));
	}
	return rects;
}