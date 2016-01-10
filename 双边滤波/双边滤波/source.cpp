#include <iostream>  
#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>   
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp> //CvtColor
using namespace cv;
using namespace std;


int main()
{
	String s1 = "input1/E";
	String s2 = "input1/I";
	String CIE = "CIE.bmp";
	String A = "A.bmp";
	String B = "B.bmp";
	String L = "L.bmp";
	Mat img = imread("input1/E.bmp");
	Mat imgI = imread("input1/I.bmp");
	Mat imgCIE=img.clone() ;
	Mat imgL(img.rows, img.cols, CV_8UC1);
	Mat imgS(img.rows, img.cols, CV_8UC1);
	Mat imgA(img.rows, img.cols, CV_8UC1);
	Mat imgB(img.rows, img.cols, CV_8UC1);
	Mat imgIL(imgI.rows, imgI.cols, CV_8UC1);
	Mat imgIA(imgI.rows, imgI.cols, CV_8UC1);
	Mat imgIB(imgI.rows, imgI.cols, CV_8UC1);
	Mat imgICIE(imgI.rows, imgI.cols, CV_8UC1);
	Mat imgIS(imgI.rows, imgI.cols, CV_8UC1);
	if (img.empty())
	{
		cout << "error";
		return -1;
	}
	imshow("RGB", imgCIE);
	cvtColor(img, imgCIE, CV_RGB2Lab);
	cvtColor(imgI, imgICIE, CV_RGB2Lab);
	for (int i = 0; i < imgCIE.rows; i++)
		for (int j = 0; j < imgCIE.cols; j++)
		{
			imgL.at<uchar>(i, j) = imgCIE.at<Vec3b>(i, j)[0];
			imgA.at<uchar>(i, j) = imgCIE.at<Vec3b>(i, j)[1];
			imgB.at<uchar>(i, j) = imgCIE.at<Vec3b>(i, j)[2];
		}
	for (int i = 0; i < imgICIE.rows; i++)
		for (int j = 0; j < imgICIE.cols; j++)
		{
			imgIL.at<uchar>(i, j) = imgICIE.at<Vec3b>(i, j)[0];
			imgIA.at<uchar>(i, j) = imgICIE.at<Vec3b>(i, j)[1];
			imgIB.at<uchar>(i, j) = imgICIE.at<Vec3b>(i, j)[2];
		}
	cvtColor(imgCIE, imgCIE, CV_Lab2RGB);
	//imwrite(s1+CIE, imgCIE);
	imwrite(s1+L, imgL);
	imwrite(s1+A, imgA);
	imwrite(s1+B, imgB);
	imwrite(s2+L, imgIL);
	imwrite(s2+A, imgIA);
	imwrite(s2+B, imgIB);
	bilateralFilter(imgL,imgS,-1,20,20);
	bilateralFilter(imgIL, imgIS, -1, 20, 20);
	Mat imgD(img.rows, img.cols, CV_8SC1);
	Mat imgID(img.rows, img.cols, CV_8SC1);
	Mat Rd(img.rows, img.cols, CV_8UC1);
	Mat Ra(img.rows, img.cols, CV_8UC1);
	Mat Rl(img.rows, img.cols, CV_8UC1);
	Mat Rs(img.rows, img.cols, CV_8SC1);
	Mat Rb(img.rows, img.cols, CV_8UC1);

	imgD = imgL - imgS;
	imgID = imgIL - imgIS;
	imwrite(s1 + "S.bmp", imgS);
	imwrite(s2 + "S.bmp", imgIS);
	imwrite(s1 + "D.bmp", imgD);
	imwrite(s2 + "D.bmp", imgID);
	Rd = 0.8*imgID + 0.2*imgD;
	imwrite("input1/Rd.bmp", Rd);
	Rs = imgIS;
	Rl = Rd + Rs;
	imwrite("input1/Rl.bmp", Rl);
	double c=0.6;
	Ra = c*imgA + (1 - c)*imgIA;
	imwrite("input1/Ra.bmp", Ra);
	Rb = c*imgB+(1 - c)*imgIB;
	imwrite("input1/Rb.bmp", Rb);
	Mat R(img.rows, img.cols, CV_8UC3);
	for (int i = 0; i < R.rows; i++)
		for (int j = 0; j < R.cols; j++)
		{
			R.at<Vec3b>(i, j)[0] = Rl.at<uchar>(i,j);
			R.at<Vec3b>(i, j)[1] = Ra.at<uchar>(i, j);
			R.at<Vec3b>(i, j)[2] = Rb.at<uchar>(i, j);
		}
	cvtColor(R, R, CV_Lab2RGB);
	imwrite("input1/R.bmp", R);
	waitKey();

	return 0;

}