#pragma once
#include <string>
#include <map>
#include <opencv2/opencv.hpp>

std::map<std::string, int> convert_to_map(cv::Rect rect);
std::vector<std::map<std::string, int>> convert_to_maps(std::vector<cv::Rect> rects);

cv::Rect convert_to_rect(std::map<std::string, int> map);
std::vector<cv::Rect> convert_to_rects(std::vector<std::map<std::string, int>> maps);