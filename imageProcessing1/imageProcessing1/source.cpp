#include<iostream>
#include <opencv2/core/core.hpp>   
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat img = imread("Art1.bmp");
	if (img.empty())
	{
		cout << "error";
		return -1;
	}
	imshow("Art1", img);
	waitKey();

	return 0;
}