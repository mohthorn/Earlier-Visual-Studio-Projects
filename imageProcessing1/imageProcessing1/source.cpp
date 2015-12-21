#include<iostream>
#include <opencv2/core/core.hpp>   
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;


int main()
{
	Mat img = imread("imgs/Art1.bmp");
	Mat dimg = imread("imgs/Art1_depth.bmp");
	Mat omg = img;
	Mat D = img;
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
	int diag = int(sqrt(img.rows*img.rows + img.cols * img.cols));
	
	cout << img.rows << endl << img.cols <<endl<<diag<< endl;
	

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
		{
			Vec3b pixel;
			pixel[0] = 0;
			pixel[1] = 0;
			pixel[2] = 0;
			img.at<Vec3b>(i, j) = pixel;
		}
	imshow("Art2", img);
	//cout << "img=" << endl << dimg << endl;
	waitKey();

	return 0;
}