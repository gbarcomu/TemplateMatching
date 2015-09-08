/*
 * Main.cpp
 *
 *  Created on: Sep 3, 2015
 *      Author: Guillermo
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "TemplateMatching.h"

int main(int argc, char** argv) {

	/// Load templates from arguments
	TemplateMatching *templateMatching = new TemplateMatching();

	cv::Mat *reader;
	for (int i = 1; argv[i] != NULL; i++) {

		reader = new cv::Mat(cv::imread(argv[i], CV_LOAD_IMAGE_COLOR));

		templateMatching->StoreImage(reader);
	}

	templateMatching->Init();

	delete templateMatching;

	return 0;
}

