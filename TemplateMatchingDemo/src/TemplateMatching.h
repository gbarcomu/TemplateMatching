/*
 * TemplateMatching.h
 *
 *  Created on: Sep 8, 2015
 *      Author: Guillermo
 */

#ifndef TEMPLATEMATCHING_H_
#define TEMPLATEMATCHING_H_

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>

class TemplateMatching {

private:

	cv::Mat img; // Image captured from web cam
	cv::Mat *templ;
	cv::Mat result;
	cv::Mat img_display;

	int imagesLoaded;

	char* imageWindow;

	bool isDemoEnded;

	int currentThreshold; // Values higher than that will be considered as success

	/*Method:
	 * 0: SQDIFF
	 * 1: SQDIFF NORMED
	 * 2: TM CCORR
	 * 3: TM CCORR NORMED
	 * 4: TM COEFF
	 * 5: TM COEFF NORMED
	 */
	static const int METHOD = 3;
	static const int MAXTHRESHOLD = 100;
	static const int DELAY = 1000;

	std::vector<cv::Mat*> *cache; // Images cache

public:
	TemplateMatching();

	void StoreImage(cv::Mat * image);

	void Init();

	void Run();

	void Match();

	~TemplateMatching();
};

#endif /* TEMPLATEMATCHING_H_ */
