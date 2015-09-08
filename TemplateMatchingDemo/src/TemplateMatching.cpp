/*
 * TemplateMatching.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: Guillermo
 */

#include "TemplateMatching.h"

TemplateMatching::TemplateMatching() {

	cache = new std::vector<cv::Mat*>;
	imagesLoaded = 0;
	imageWindow = "Source Image";
	isDemoEnded = false;
}

void TemplateMatching::StoreImage(cv::Mat* image) {

	cache->push_back(image);
	imagesLoaded++;
}

void TemplateMatching::Init() {

	std::cout << "Loaded images: " << imagesLoaded << std::endl;

	std::cout << "Creating Window... " << std::endl;
	cv::namedWindow(imageWindow, CV_WINDOW_AUTOSIZE);

	std::cout << "Adding Trackbar... " << std::endl;
	cv::createTrackbar("Accuracy", imageWindow, &currentThreshold,
			MAXTHRESHOLD);

	Run();
}

void TemplateMatching::Run() {

	cv::VideoCapture cap(0);

	while (!isDemoEnded) {

		bool bSuccess = cap.read(img); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			std::cout << "Cannot read a frame from video stream" << std::endl;
			break;
		}

		Match();

		cv::imshow(imageWindow, img_display);

		if (cv::waitKey(DELAY) != -1) {

			isDemoEnded = true;
		}
	}
}

void TemplateMatching::Match() {

	img.copyTo(img_display);

	for (int i = 0; i < imagesLoaded; i++) {

		std::cout << "Image: " << i << std::endl;

		templ = cache->operator [](i);

		int result_cols = img.cols - (*templ).cols + 1;
		int result_rows = img.rows - (*templ).rows + 1;

		result.create(result_rows, result_cols, CV_32FC1);
		cv::matchTemplate(img, (*templ), result, METHOD);

		double minVal;
		double maxVal;
		double matchVal;
		cv::Point minLoc;
		cv::Point maxLoc;
		cv::Point matchLoc;

		double thresholdValue = (double) currentThreshold / 100;

		cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

		if (METHOD <= 1) {
			matchLoc = minLoc;
			matchVal = minVal;
		} else {
			matchLoc = maxLoc;
			matchVal = maxVal;
		}

		std::cout << "MatchVal: " << matchVal << std::endl;
		std::cout << "Threshold: " << thresholdValue << std::endl;

		if (matchVal > thresholdValue) { // Should be < if METHOD == 1 or 0

			cv::rectangle(img_display, matchLoc,
					cv::Point(matchLoc.x + (*templ).cols,
							matchLoc.y + (*templ).rows), cv::Scalar::all(0),
					2 + (i * 2), 8, 0);
		}
	}
}

TemplateMatching::~TemplateMatching() {

	cv::Mat *eraser;

	while (!cache->empty()) {

		eraser = cache->back();
		cache->pop_back();
		delete eraser;
	}
	delete cache;
}

