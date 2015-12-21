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
	String pics[8] = { "Art1","Bowling1","cones","Dolls","Flowerpots","Laundry1","Moebius1","teddy" };
	int m[100][100];
	for (int ii = 0; ii < 8; ii++)
	{
		String s1 = "imgs/" + pics[ii] + ".bmp";
		String s2= "imgs/" + pics[ii] + "_depth.bmp";
		Mat img = imread(s1);
		Mat dimg = imread(s2);
		Mat dimg2 = imread(s2);
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

		//imshow("Art1", img);
		//imshow("Art1_D", dimg);
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
		GaussianBlur(dimg, omg, Size(31, 31), 0, 0);
		//imshow("gauss", omg);

		//imshow("DD", DD);

		DD = omg - dimg2;
		//imshow("DD", DD);
		//imshow("Art21", img);
		img -= (3 * DD);
		String s3= "imgs/" + pics[ii] + "_out.bmp";
		imwrite(s3, img);
	}
	waitKey();

	return 0;
}