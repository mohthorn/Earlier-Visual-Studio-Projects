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
	double m[100][100];		//mask

	for (int ii = 0; ii < 8; ii++)
	{
		String s1 = "imgs/" + pics[ii] + ".bmp";//读图
		String s2= "imgs/" + pics[ii] + "_depth.bmp";
		Mat img = imread(s1);	//彩色原图
		Mat dimg = imread(s2,0);	//深度图
		Mat dimg2 = imread(s2);
		Mat dimg3 = imread(s2,0);
		Mat omg = dimg3;		//高斯模糊深度图
		Mat DD = dimg3;			//差别图

		if (img.empty())
		{
			cout << "error";
			return -1;
		}
		if (dimg.empty())
		{
			cout << endl << "derror";
		}
		if (dimg2.empty())
		{
			cout << endl << "d2error";
		}
		if (dimg3.empty())
		{
			cout << endl << "d3error";
		}
		int diag = int(sqrt(img.rows*img.rows + img.cols * img.cols));		
		cout << img.rows << endl << img.cols <<endl<<diag<< endl;
		/*	高斯滤波*/	
		int k = 13; //确定kernel
		/*cin >> k;*/
		double w = 0;
		for (int i = 0; i < 2 * k + 1; i++)
		{
			for (int j = 0; j < 2 * k + 1; j++)
			{
				int dis = (i - k)*(i - k) + (j - k)*(j - k);
				double g = 1.0 / (2 * PI*k*k)*exp(-dis*1.0 / (2 * k*k));	//通过高斯函数得到值
				m[i][j] = g;
				w += g;
			}
		}
		for (int i = 0; i < 2 * k + 1; i++)
		{

				for (int j = 0; j < 2 * k + 1; j++)
				{
					
					m[i][j] /= (0.99*w);
					cout << m[i][j] << " ";
				}
				cout << endl;

		}
		
		for (int i = 0; i < dimg.rows; i++)
		{
			for (int j = 0; j < dimg.cols; j++)
			{
				double nd=0;
				for (int kk = 0; kk < 2 * k + 1; kk++)
				{
					for (int jj = 0; jj < 2 * k + 1; jj++)
					{
						
						int ni = i +k-kk;
						int nj=j+k-jj;
						
						if (ni < 0)
							ni = -ni;
						if (ni > dimg3.rows-1)
							ni = dimg3.rows-1-(ni-dimg3.rows+1);

						
						if (nj < 0)
							nj = -nj;
						if (nj > dimg3.cols-1)
							nj = dimg3.cols-1-(nj-dimg3.cols+1);
						uchar ndij = dimg.at<uchar>(ni, nj);
						nd += (m[kk][jj] * ndij);
							
					}
				}
				omg.at<uchar>(i, j) = (int)nd;
			}
		}
		//imshow("blur", omg);
		//imshow("origin", dimg);
		String s5 = "imgs/" + pics[ii] + "_new.bmp";
		imwrite(s5, omg);
		omg = imread(s5);
		//GaussianBlur(dimg, omg, Size(27, 27), 0, 0);
		//imshow("gauss", omg);

		//imshow("DD", DD);

		//输出图像
		DD = omg - dimg2;
		String s4 = "imgs/" + pics[ii] + "_diff.bmp";
		imwrite(s4, DD);
		//imshow("DD", DD);
		//imshow("Art21", img);
		img -= (1.4 * DD);
		String s3= "imgs/" + pics[ii] + "_out.bmp";
		imwrite(s3, img);
	}
	waitKey();

	return 0;
}