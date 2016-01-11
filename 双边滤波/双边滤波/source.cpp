#include <iostream>  
#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>   
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp> //CvtColor
using namespace cv;
using namespace std;
//int x[700][700];
//int y[700][700];
//int z[700][700];
double f(double t)
{
	if (t > pow(3.0/ 69, (3.0)))
		return pow(t, (1.0 / 3.0));
	else
		return (1.0 / 3.0*pow(29.0 / 6.0, 2.0) + 4.0 / 29.0);
}

double g(double t)
{
	if (t > 0.04045)
		return pow((t + 0.055) / 1.055, 2.4);
	else
		return t*1.0 / 12.92;
}

Mat RGB2Lab(Mat in)
{
	Mat out(in.rows,in.cols,CV_8UC3);
	Mat x(in.rows, in.cols, CV_8UC1,Scalar(0));
	Mat y(in.rows, in.cols, CV_8UC1, Scalar(0));
	Mat z(in.rows, in.cols, CV_8UC1, Scalar(0));

	Mat L(in.rows, in.cols, CV_8UC1, Scalar(0));
	Mat a(in.rows, in.cols, CV_8SC1, Scalar(0));
	Mat b(in.rows, in.cols, CV_8SC1, Scalar(0));
	Mat R(in.rows, in.cols, CV_8UC1);
	Mat G(in.rows, in.cols, CV_8UC1);
	Mat B(in.rows, in.cols, CV_8UC1);
	double m1[3][3] = { 0.412453,0.357580,0.180423,
						0.212671,0.715160,0.072169,
						0.019334,0.119193,0.950227 };
	double xn = 1.0000; 
	double yn = 1.0000; 
	double zn = 1.0000;
	//for (int i = 0; i < in.rows; i++)
	//	for (int j = 0; j < in.cols; j++)
	//	{
	//		R.at<uchar>(i, j) = in.at<Vec3b>(i, j)[0];
	//		G.at<uchar>(i, j) = in.at<Vec3b>(i, j)[1];
	//		B.at<uchar>(i, j) = in.at<Vec3b>(i, j)[2];
	//	}
	
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			
			for (int k = 0; k < 3;k++)
			{ 
				int p = in.at<Vec3b>(i, j)[k];
				x.at<uchar>(i,j) += (m1[0][k] * in.at<Vec3b>(i, j)[k] /*/ 255.0*/);
				y.at<uchar>(i,j) += (m1[1][k] * in.at<Vec3b>(i, j)[ k] /*/ 255.0*/);
				z.at<uchar>(i,j) +=( m1[2][k] * in.at<Vec3b>(i, j)[ k]  /*/ 255.0*/);
			}
			
		}
	
	//for (int i = 0; i < 20; i++)
	//{
	//	for (int j = 0; j < 20; j++)
	//	{
	//		cout << x[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//imshow("in1", in);
	//imshow("x", x);
	//imshow("y", y);
	//imshow("z", z);
	//for (int i = 0; i < in.rows; i++)
	//	for (int j = 0; j < in.cols; j++)
	//	{
	//		/*double d = y.at<double>(i, j) / yn;*/
	//		double d = y.at<uchar>(i, j)*1.0 / yn/255.0;
	//		double d2 = x.at<uchar>(i, j)*1.0 / xn/255.0;
	//		double d3 = z.at<uchar>(i, j)*1.0 / zn/255.0;
	//		L.at<uchar>(i, j) = 116 * f(d) - 16;
	//		//a.at<uchar>(i, j) = (uchar)(500 * (f(x.at<double>(i, j) / xn) - f(y.at<double>(i, j) / yn)));
	//		//b.at<uchar>(i, j) = (uchar)(200 * (f(y.at<double>(i, j) / yn) - f(z.at<double>(i, j) / zn)));
	//		//a.at<uchar>(i, j) = (uchar)(500 * (f(x[i][j]/ xn) - f(y[i][j]/ yn)));
	//		//b.at<uchar>(i, j) = (uchar)(200 * (f(y[i][j] / yn) - f(z[i][j]/ zn)));
	//		a.at<uchar>(i, j) = 500*(f(d2)-f(d));
	//		b.at<uchar>(i, j) = 116 * f(d3) - 16;
	//	}

	L = 166 * y / 255.0 - 16;
	a = 500.0/255 * (x - y) ;
	b = 200.0/255 * (y - z) ;
	//imshow("in2", in);
	imshow("L", L);
	imshow("a", a);
	imshow("b", b);
	
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			out.at<Vec3b>(i, j)[0] = L.at<uchar>(i, j);
			out.at<Vec3b>(i, j)[1] = a.at<uchar>(i, j);
			out.at<Vec3b>(i, j)[2] = b.at<uchar>(i, j);
		}
	//imshow("x", x);
	//imshow("y", y);
	//imshow("z", z);
	imshow("out1", out);
	return out;
}

Mat mbilateral(Mat in, int k, int sigmad, int sigmar)
{
	int m[100][100];
	for (int p = 0; p < 2 * k + 1; p++)
		for (int q = 0; q < 2 * k + 1; q++)
		{
			m[p][q]= (q - k)*(q - k) + (p - k)*(p - k);
		}
	Mat out(in.rows, in.cols, CV_8UC1,Scalar(0));

	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			double sum = 0;
			double sum2 = 0;
			for (int p = 0; p < 2 * k + 1; p++)
			{
				for (int q = 0; q < 2 * k + 1; q++)
				{
					int dis;
					
					dis = m[p][q];
					int np=i+p-k; 
					int nq=j+q-k;			//计算每个像素点映射的领域点


					if (np < 0)					//边界情况，取镜像
						np = -np;
					if (np > in.rows - 1)
						np = in.rows - 1 - (np - in.rows + 1);
					if (nq < 0)
						nq = -nq;
					if (nq > in.cols - 1)
						nq = in.cols - 1 - (nq - in.cols + 1);
					//uchar ndij = dimg.at<uchar>(ni, nj);

					int inte = (in.at<uchar>(np, nq) - in.at<uchar>(i, j))*(in.at<uchar>(np, nq) - in.at<uchar>(i, j));
					

					double bf=exp(-(double)dis/(2.0*sigmad*sigmad))*exp(-(double)inte/(2.0*sigmar*sigmar));
					sum += bf;
					bf *= in.at<uchar>(np, nq);
					sum2 += bf;		//计算卷积

				}

			}
			sum = sum2 / sum;
			out.at<uchar>(i, j) = (uchar)sum;
			//for (int i = 0; i < 2 * k + 1; i++)
			//{

			//	for (int j = 0; j < 2 * k + 1; j++)
			//	{

			//		m[i][j] /= (0.999*w);		//修正可能的浮点数误差，尽量靠近1
			//									//cout << m[i][j] << " ";
			//	}
			//	//cout << endl;

			//}
		}
	return out;
}

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
	//imshow("RGB", imgCIE);
	//imgCIE=RGB2Lab(imgCIE);
	//cvtColor(imgCIE, imgCIE, CV_Lab2RGB);
	//imshow("out", imgCIE);
	cvtColor(img, imgCIE, CV_RGB2Lab);		//颜色空间转换
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
	bilateralFilter(imgL,imgS,-1,10,10);			//双边滤波
	imwrite(s1 + "SO.bmp", imgS);
	//bilateralFilter(imgIL, imgIS, -1, 20, 20);
		//双边滤波库函数

	bilateralFilter(imgIL, imgIS, -1, 10, 10);
	imwrite(s2 + "SO.bmp", imgIS);

	imgS = mbilateral(imgL, 9, 10, 10);		//手写双边滤波
	imgIS = mbilateral(imgIL, 9, 10, 10);


	Mat imgD(img.rows, img.cols, CV_16SC1);
	Mat imgID(img.rows, img.cols, CV_16SC1);
	Mat Rd(img.rows, img.cols, CV_8UC1);
	Mat Ra(img.rows, img.cols, CV_8SC1);
	Mat Rl(img.rows, img.cols, CV_8SC1);
	Mat Rs(img.rows, img.cols, CV_8SC1);
	Mat Rb(img.rows, img.cols, CV_8SC1);

	imgD = imgL - imgS;
	imgID = imgIL - imgIS;
	imwrite(s1 + "S.bmp", imgS);
	imwrite(s2 + "S.bmp", imgIS);


	Rd = 0.8*imgID + 0.2*imgD;
	imwrite("input1/Rd.bmp", Rd);
	Rs = imgIS;
	Rl = Rd + Rs;
	imwrite("input1/Rl.bmp", Rl);
	double c=0.8;
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

	Mat imgONE(img.rows, img.cols, CV_8UC1, Scalar(1));
	imgD = imgD + 128 * imgONE;
	imgID = imgID + 128 * imgONE;
	imwrite(s1 + "D.bmp", imgD);
	imwrite(s2 + "D.bmp", imgID);

	imwrite("input1/R.bmp", R);
	waitKey();

	return 0;

}