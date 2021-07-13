#include <iostream>
#include <vector>
#include<opencv2/core/core.hpp>
#include<opencv2/core/mat.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
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
//Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table) {
//	//  accept only char type matrices
//	CV_Assert(I.depth() == CV_8U);
//
//	const int channels = I.channels();
//
//	switch (channels)
//	{
//	case 1:
//	{
//		for (int i = 0; i < I.rows; ++i) {
//			for (int j = 0; j < I.cols; ++j) {
//				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
//			}
//
//		}
//
//		
//		break;
//	}
//
//	case 3:
//	{
//		Mat_<Vec3b> _I = I;
//
//		for (int i = 0; i < I.rows; ++i) {
//			for (int j = 0; j < I.cols; ++j) {
//				_I(i, j)[0] = table[_I(i, j)[0]];
//				_I(i, j)[1] = table[_I(i, j)[1]];
//				_I(i, j)[2] = table[_I(i, j)[2]];
//			}
//		}
//
//		I = _I;
//		break;
//
//	}
//
//	}
//	return I;
//
//
//}

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
//void main() {
//	
//	int divideWith = 10; // convert our input string to number - C++ style
//	uchar table[256];
//	for (int i = 0; i < 256; ++i)
//		table[i] = (uchar)(divideWith * (i / divideWith));
//
//	//![table-init]
//	Mat lookUpTable(1, 256, CV_8U);//构建一个Mat类型变量，1行256列。8位uchar
//	uchar* p = lookUpTable.ptr();
//	for (int i = 0; i < 256; ++i) {
//		p[i] = table[i];//通过ptr（）指针，将table[i]的值赋给lookUpTable矩阵
//	}
//
//	Mat c = imread("Resources/waitSR.jpg");
//	if (c.data == NULL) {
//		cout << "read failed" << endl;
//		exit(1);
//	}
//
//	Mat J;
//	LUT(c, lookUpTable, J);
//	imshow("before ", c);
//	waitKey(0);
//	imshow("after ", J);
//	waitKey(0);
//	//! [table-init]
//}


////////////////////////////////////////////////////////!卷积初试
void Sharpen(const Mat& myImage, Mat& Result);

int main(int argc, char* argv[]) {
	/*
	Hand written function time passed in seconds: 0.008001
	Built-in filter2D time passed in seconds:  0.0028362
	*/

	const char* filename = argc >= 2 ? argv[1] : "waitSR.jpg";
	
	Mat src, dst0, dst1;

	src = imread(samples::findFile(filename), IMREAD_COLOR);

	if (src.empty())
	{
		cerr << "Cant open image [" << filename << "]" << endl;
		return EXIT_FAILURE;
	}

	namedWindow("Input", WINDOW_AUTOSIZE);
	namedWindow("Output", WINDOW_AUTOSIZE);/////??????????

	imshow("Input", src);
	double t = (double)getTickCount();

	Sharpen(src, dst0);

	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Hand written function time passed in seconds: " << t << endl;


	imshow("Output", dst0);
	waitKey();


	Mat kernel = (Mat_<char>(3, 3) << 
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0);

	t = (double)getTickCount();
	filter2D(src, dst1, src.depth(), kernel);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Built-in filter2D time passed in seconds:  " << t << endl;

	imshow("Output2", dst1);
	waitKey();

	/*filter2D()，该函数甚至还有第五个可选参数来指定内核的中心，第六个参数用于在将过滤后的像素存储到K中之前向它们添加一个可选值，第七个参数用于决定在未定义操作的区域(边界)中执行什么操作。*/



	return EXIT_SUCCESS;
}


void Sharpen(const Mat& myImage, Mat& Result) {
	CV_Assert(myImage.depth() == CV_8U);//accept only uchar images

	const int nchannels = myImage.channels();
	Result.create(myImage.size(), myImage.type());

	for (int j = 1; j < myImage.rows - 1; ++j) {
		const uchar* previous = myImage.ptr<uchar>(j - 1);
		const uchar* current = myImage.ptr<uchar>(j);
		const uchar* next = myImage.ptr<uchar>(j + 1);

		uchar* output = Result.ptr<uchar>(j);

		for (int i = nchannels; i < nchannels * (myImage.cols - 1); ++i)
		{
			*output++ = saturate_cast<uchar>(
				5 * current[i] - current[i - nchannels] - current[i + nchannels] - previous[i] - next[i]);
			//每次算术操作后，移动指针一字节。它的确是从第一行，第一列开始的。而不是像current那样
		}

	}
	//cout << Result << endl;
	Result.row(0).setTo(Scalar(0));
	Result.row(Result.rows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(Result.cols - 1).setTo(Scalar(0));
	//但即使不置零，图像看起来也没什么差别。
	//On the borders of the image
	//the upper notation results inexistent pixel locations(like minus one - minus one).
	//In these points our formula is undefined.
	//A simple solution is to not apply the kernel in these pointsand, for example, set the pixels on the borders to zeros :

}
//////!卷积初试


////////////////////////////////////////!ptr<>()
//void main() {
//	Mat j(10, 10, CV_8UC3,Scalar(1,1,3)),result;
//	Sharpen(j, result);
//	cout <<endl<< result << endl;
//	//cout << j << endl;
//}
//////////////!ptr<>()















