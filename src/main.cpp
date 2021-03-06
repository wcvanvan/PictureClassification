#pragma once
#include <cstring>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>
#include "cnn_network.hpp"
#include "matrix.hpp"
using namespace std;

int main() {
	cv::Mat img = cv::imread("D:\\Projects\\PictureClassification\\pics\\lena.jpg");
	cv::resize(img, img, cv::Size(128, 128));
	img.convertTo(img, CV_32FC3, 1.0 / 255.0);
	cv::Mat mats[3];
	cv::split(img, mats);
	float *mat_data = new float[3*128*128];
	size_t channel_size = 128 * 128;
	memcpy(mat_data, mats[0].ptr<float>(0), sizeof(float)*channel_size);
	memcpy(&mat_data[channel_size], mats[1].ptr<float>(0), sizeof(float) * channel_size);
	memcpy(&mat_data[channel_size*2], mats[2].ptr<float>(0), sizeof(float) * channel_size);
	float result_bg = 0., result_face = 0.;

	clock_t start_time, end_time;
	if (mat_data != nullptr) {
		Matrix<float> matrix(img.rows, img.cols, img.channels(), mat_data);
		start_time = clock();
		build_network(matrix, result_bg, result_face);
		end_time = clock();
	}
	else {
		std::cout << "No pic" << std::endl;
	}
	cout << "background score: " << result_bg << ", " << "face score: " << result_face << endl;
	cout << "takes time: " << double(end_time - start_time) / (CLOCKS_PER_SEC/1000) << "ms" << endl;
}

