#include <iostream>
#include <vector>
#include<opencv2/core/core.hpp>
#include<opencv2/core/mat.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

//
//int main() {
//	/*Mat A(2, 2, CV_8UC3, Scalar(0, 0, 255));
//	cout << "A= " << endl << " " << A << endl;*/
//
//
//    //Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
//    //cout << "C = " << endl << " " << C << endl << endl;
//
//    //C = Mat_<double>({ 0,-1,0,-1,-5,-1,0,-1,0,3 }).reshape(5,2);
//    //cout << "C = " << endl << " " << C << endl << endl;
//
//    //Mat R = Mat(3, 2, CV_8UC3);
//    //randu(R, Scalar::all(0), Scalar::all(255));
//    //cout << "R (default) = " << endl << R << endl << endl;
//    //
//    //Range a(0, 4);
//    //cout << "a= " << a << endl;
//   
//    ///////////////////////////////////////////////////指针对齐
//    /*float c[4] = { 1,2,3,4 };
//    float* p=c;
//    float* q=NULL;
//    float n = 4;
//    printf("p=%p\nq=%p\n", p, q);
//    q=alignPtr<float>(p);
//    printf("p=%p\nq=%p\n", p, q);*/
//
//
//    //Mat E = Mat::eye(4, 4, CV_64F);
//    //cout << "E = " << endl << " " << E << endl << endl;
//    //Mat O = Mat::ones(2, 2, CV_32F);
//    //cout << "O = " << endl << " " << O << endl << endl;
//    //Mat Z = Mat::zeros(3, 3, CV_8UC1);
//    //cout << "Z = " << endl << " " << Z << endl << endl;
//
//    ////学习opencv的P65 页。
//    //Mat m;
//    ////create data area for 3 rows and 10 columns of 3-channel 32-bit floats.
//    //m.create(3, 10, CV_32FC3);
//    //
//    ////set the values in the 1st channel to 1.0 , the 2nd to 0.0, and the 3rd to 1.0 
//    //m.setTo(Scalar(1.0f, 0.0f, 2.0f));
//
//    //cout << m << endl;
//    //
//    //Mat c(3, 10, CV_32FC3, Scalar(1.0f, 0.0f, 2.0f));
//    //cout << c << endl;
//
//
//    //Vec<float, 10>a{ 1,2,3,4,5,6,7,8,9,1 };
//
//    //Mat d;
//    //d = Mat(a);
//    //cout << d << endl;
//
//    //Mat f;
//    //f = Mat::eye(10, 10, CV_32FC1);
//    //cout << f.at<float>(3, 3) << endl;
//
//
//    ////使用Mat::eye()和Mat::ones()的时候，如果要求创建的是一个多维数组，就只有第一通道会被设置为1，其余通道保持为0.
//    //Mat h = Mat::eye(10, 10, CV_32FC2);
//    //cout << "Element (3,3) is "
//    //    << h.at<Vec2f>(3, 3)[0] << ", "
//    //    << h.at<Vec2f>(3, 3)[1] << endl;
//    //cout << h << endl;
//    //cout << h.at<Vec2f>(1, 1) << endl;
//
//     int sz[3] = { 3,3 };
//    Mat k(2,sz, CV_64FC3,Scalar(1,2,3));
//    cout << (k.type()==CV_64FC4) << endl;
//    cout << k << endl;
//    cout << k.at<Vec3f>(0,3) << endl;
//    //自定义数据类型
//    typedef cv::Vec<double, 5> Vec5d;
//    //生成一个2x3x5的Mat，数据为double型
//    Mat m1 = Mat(2, 3, CV_64FC(5));
//    cout << m1.channels() << "channels" << endl;
//    for (int i = 0; i < m1.rows; i++) {
//        for (int j = 0; j < m1.cols; j++) {
//            for (int c = 0; c < m1.channels(); c++) {
//                //给m1的每一个元素赋值
//                m1.at<Vec5d>(i, j)[c] = c * 0.01;
//
//            }
//        }
//    }
//    cout << m1 << endl;
//
//  
//}


///////////////////The iterator (safe) method
//https://docs.opencv.org/4.5.2/db/da5/tutorial_how_to_scan_images.html
//Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table) {
//	//  accept only char type matrices
//	CV_Assert(I.depth() == CV_8U);
//
//	const int channels = I.channels();
//
//	switch (channels)
//	{
//	case 1:
//	{
//		MatIterator_<uchar> it, end;
//		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
//			*it = table[*it];
//		break;
//	}
//
//	case 3:
//		{
//		MatIterator_<Vec3b> it, end;
//		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) 
//		{
//			(*it)[0] = table[(*it)[0]];
//			(*it)[1] = table[(*it)[1]];
//			(*it)[2] = table[(*it)[2]];
//		}
//		}
//	
//	}
//	return I;
//
//
//}

//////////////////////////////////////////////using Mat::at() for pass through image
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table) {
	//  accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	const int channels = I.channels();

	switch (channels)
	{
	case 1:
	{
		for (int i = 0; i < I.rows; ++i) {
			for (int j = 0; j < I.cols; ++j) {
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
			}

		}

		
		break;
	}

	case 3:
	{
		Mat_<Vec3b> _I = I;

		for (int i = 0; i < I.rows; ++i) {
			for (int j = 0; j < I.cols; ++j) {
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		}

		I = _I;
		break;

	}

	}
	return I;


}

//void main() {
//	int divideWith = 10; // convert our input string to number - C++ style
//	uchar table[256];
//	for (int i = 0; i < 256; ++i)
//		table[i] = (uchar)(divideWith * (i / divideWith));
//
//	Mat a;
//	String path = "Resources/waitSR.jpg";
//	a = imread(path);
//	if (a.data == NULL) {
//		cout << "read failed" << endl;
//		exit(1);
//	}
//
//	Mat m(512, 512, CV_8UC3, Scalar(200, 255, 3));
//	//cout << m << endl;
//	imshow("ii", a);
//	waitKey(0);
//
//	ScanImageAndReduceIterator(a, table);
//  ScanImageAndReduceRandomAccess(a, table);
//	imshow("after", a);
//
//	waitKey(0);
//	//cout << m << endl;
//}

/// <summary>
/// /////////////////////////////////////////the fast way without writing the logic of scanning image .
/// </summary>

void main() {
	const int times = 100;
	int divideWith = 10; // convert our input string to number - C++ style
	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(divideWith * (i / divideWith));

	//![table-init]
	Mat lookUpTable(1, 256, CV_8U);//构建一个Mat类型变量，1行256列。8位uchar
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i) {
		p[i] = table[i];//通过ptr（）指针，将table[i]的值赋给lookUpTable矩阵
	}

	Mat c = imread("Resources/waitSR.jpg");
	if (c.data == NULL) {
		cout << "read failed" << endl;
		exit(1);
	}

	Mat J;
	LUT(c, lookUpTable, J);
	imshow("before ", c);
	waitKey(0);
	imshow("after ", J);
	waitKey(0);
	//! [table-init]
}



