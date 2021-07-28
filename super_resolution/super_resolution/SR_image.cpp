#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "superResolution.h"

using namespace cv;
using namespace std;
#define test112 1


int main() {
	Mat image = imread("Resources/waitSR.jpg",IMREAD_UNCHANGED);
	if (image.empty()) {
		cerr << "Can not load the image file :" << "waitSR.jpg" << endl;
		return -1;
	}

	////´òÓ¡Í¼ÏñÖµ
#if test112
		for (int ch = 0; ch < image.channels(); ch++) {
			cout << "The original input \n" << ch << " channel= (\n" << (int)image.at<Vec3b>(0, 0)[ch] << "\t" << (int)image.at<Vec3b>(0, 1)[ch] << " ... " << (int)image.at<Vec3b>(0, image.cols - 1)[ch] << endl
				<< (int)image.at<Vec3b>(1, 0)[ch] << "\t" << (int)image.at<Vec3b>(1, 1)[ch] << " ... " << (int)image.at<Vec3b>(1, image.cols-1)[ch] << endl
				<< " , ..., " << endl
				<< (int)image.at<Vec3b>(image.rows-1, 0)[ch] << "\t" << (int)image.at<Vec3b>(image.rows-1, 1)[ch] << " ... " << (int)image.at<Vec3b>(image.rows-1, image.cols-1)[ch] << endl

				<< " )" << endl;
		}

#endif


	//imshow("asd", image);
	//waitKey(0);
	superResolution(image.ptr(0), image.cols, image.rows, (int)image.step);
	cout << "success" << endl<<image.channels();
	waitKey(0);
	return 0;
}