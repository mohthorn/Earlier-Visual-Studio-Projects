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
	double k = 6; //确定kernel
	/*cin >> k;*/
	double w = 0;
	for (int i = 0; i < 2 * k + 1; i++)
	{
		for (int j = 0; j < 2 * k + 1; j++)
		{
			int dis = (i - (int)k)*(i - (int)k) + (j - (int)k)*(j - (int)k);
			double g = 1.0 / (2 * PI*k*k/2)*exp(-dis*1.0 / (2*k*k/2));

			m[i][j] = g;
			w += g;			//w值用于归一化
		}
	}
	for (int i = 0; i < 2 * k + 1; i++)
	{

		for (int j = 0; j < 2 * k + 1; j++)
		{

			m[i][j] /= (0.999*w);		//修正可能的浮点数误差，尽量靠近1
			//cout << m[i][j] << " ";
		}
		//cout << endl;

	}
	for (int ii = 0; ii < 8; ii++)
	{
		String s1 = "imgs/" + pics[ii] + ".bmp";//读图
		String s2= "imgs/" + pics[ii] + "_depth.bmp";
		Mat img = imread(s1);	//彩色原图
		Mat img1 = imread(s1);
		Mat dimg = imread(s2,0);	//深度图
		Mat dimg2 = imread(s2);		//两个单通道图用于高斯滤波的计算，
		Mat dimg3 = imread(s2,0);	//一个RGB图用于图片的加减运算
		Mat omg = dimg3;		//高斯模糊深度图
		Mat DD = dimg3;			//差别图


		if (img.empty())			//错误检查
		{
			cout << "error";
			return -1;
		}
		if (img1.empty())			//错误检查
		{
			cout << "i1error";
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
		cout << "Processing image" << s1<<endl;
		cout << "row: "<<img.rows << endl << "cols: "<<img.cols <<endl<<"diag: "<<diag<< endl;
		/*	高斯滤波*/	
	
		for (int i = 0; i < dimg.rows; i++)			//四重循环，外层遍历每个像素点，内层遍历邻域，得出G*D
		{
			if(i%10==0)
			cout << ".";							//进度显示
			for (int j = 0; j < dimg.cols; j++)
			{
				
				double nd=0;						//nd代表单个像素G*D的值
				for (int kk = 0; kk < 2 * k + 1; kk++)
				{
					for (int jj = 0; jj < 2 * k + 1; jj++)
					{	
																	
						int ni = i +k-kk;			//计算每个像素点映射的领域点
						int nj=j+k-jj;
						
						if (ni < 0)					//边界情况，取镜像
							ni = -ni;
						if (ni > dimg3.rows-1)
							ni = dimg3.rows-1-(ni-dimg3.rows+1);						
						if (nj < 0)
							nj = -nj;
						if (nj > dimg3.cols-1)
							nj = dimg3.cols-1-(nj-dimg3.cols+1);
						uchar ndij = dimg.at<uchar>(ni, nj);	
						nd += (m[kk][jj] * ndij);		//计算卷积
							
					}
				}
				omg.at<uchar>(i, j) = (uchar)nd;
			}
		}
		cout <<"Komplete!"<< endl;

		String s5 = "imgs/" + pics[ii] + "_new.bmp";
		imwrite(s5, omg);				//因为不会将单通道图转为多通道图，因此采用比较容易										//
		omg = imread(s5);				//想到的先写入单通道图，再作为多通道图读取
										//在大量图片处理时可能因为硬盘读写损失效率
		//GaussianBlur(dimg, omg, Size(13, 13), 0, 0);
		//imshow("gauss", omg);


		//输出图像
		DD = omg - dimg2;
		String s4 = "imgs/" + pics[ii] + "_diff.bmp";
		imwrite(s4, DD);

		img -= (1.4 * DD);
		String s3= "imgs/" + pics[ii] + "_out.bmp";
		imwrite(s3, img);

		dimg2 = img1 - img;
		String s6 = "imgs/" + pics[ii] + "_diff2.bmp";
		imwrite(s6, dimg2);
	}
	//waitKey();

	return 0;
}