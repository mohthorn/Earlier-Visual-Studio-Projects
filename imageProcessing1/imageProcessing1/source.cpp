#include<iostream>
#include <opencv2/core/core.hpp>   
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#define PI 3.14
using namespace std;
using namespace cv;


int main()
{
	int m[100][100];
	
	Mat img = imread("imgs/Art1.bmp");
	Mat dimg = imread("imgs/Art1_depth.bmp");
	Mat dimg2= imread("imgs/Art1_depth.bmp");
	Mat omg = dimg;
	Mat DD = dimg2;
	if (img.empty())
	{
		cout << "error";
		return -1;
	}
	if (dimg.empty())
	{
		cout << endl << "derror";
	}

	imshow("Art1", img);
	imshow("Art1_D", dimg);
	//int diag = int(sqrt(img.rows*img.rows + img.cols * img.cols));
	//
	//cout << img.rows << endl << img.cols <<endl<<diag<< endl;
//¸ßË¹ÂË²¨	
	//int k = 5;
	//cin >> k;
	//for (int i = 0; i < 2 * k + 1; i++)
	//{
	//	for (int j = 0; j < 2 * k + 1; j++)
	//	{
	//		int dis = (i - k)*(i - k) + (j - k)*(j - k);
	//		m[i][j] = 0;
	//	}
	//}
	//for (int i = 0; i < 2 * k + 1; i++)
	//{
	//	for (int j = 0; j < 2 * k + 1; j++)
	//	{
	//		cout<<m[i][j]<<" ";
	//	}
	//	cout << endl;
	//}
	GaussianBlur(dimg, omg, Size(7, 7), 0, 0);
	imshow("gauss", omg);

	imshow("DD", DD);

	DD = omg - dimg2;
	imshow("DD", DD);
	imshow("Art21", img);
	img -= (3*DD);

	imshow("Art2", img);

	waitKey();

	return 0;
}