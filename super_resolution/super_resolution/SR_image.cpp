#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "superResolution.h"

using namespace cv;
using namespace std;

int main() {
	Mat image = imread("Resources/waitSR.jpg");
	if (image.empty()) {
		cerr << "Can not load the image file :" << "waitSR.jpg" << endl;
		return -1;
	}

	superResolution(image.ptr(0), image.cols, image.rows, (int)image.step);
	cout << "success" << endl<<image.channels();
	waitKey(0);
	return 0;
}