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
	double k = 6; //ȷ��kernel
	/*cin >> k;*/
	double w = 0;
	for (int i = 0; i < 2 * k + 1; i++)
	{
		for (int j = 0; j < 2 * k + 1; j++)
		{
			int dis = (i - (int)k)*(i - (int)k) + (j - (int)k)*(j - (int)k);
			double g = 1.0 / (2 * PI*k*k/2)*exp(-dis*1.0 / (2*k*k/2));

			m[i][j] = g;
			w += g;			//wֵ���ڹ�һ��
		}
	}
	for (int i = 0; i < 2 * k + 1; i++)
	{

		for (int j = 0; j < 2 * k + 1; j++)
		{

			m[i][j] /= (0.999*w);		//�������ܵĸ���������������1
			//cout << m[i][j] << " ";
		}
		//cout << endl;

	}
	for (int ii = 0; ii < 8; ii++)
	{
		String s1 = "imgs/" + pics[ii] + ".bmp";//��ͼ
		String s2= "imgs/" + pics[ii] + "_depth.bmp";
		Mat img = imread(s1);	//��ɫԭͼ
		Mat img1 = imread(s1);
		Mat dimg = imread(s2,0);	//���ͼ
		Mat dimg2 = imread(s2);		//������ͨ��ͼ���ڸ�˹�˲��ļ��㣬
		Mat dimg3 = imread(s2,0);	//һ��RGBͼ����ͼƬ�ļӼ�����
		Mat omg = dimg3;		//��˹ģ�����ͼ
		Mat DD = dimg3;			//���ͼ


		if (img.empty())			//������
		{
			cout << "error";
			return -1;
		}
		if (img1.empty())			//������
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
		/*	��˹�˲�*/	
	
		for (int i = 0; i < dimg.rows; i++)			//����ѭ����������ÿ�����ص㣬�ڲ�������򣬵ó�G*D
		{
			if(i%10==0)
			cout << ".";							//������ʾ
			for (int j = 0; j < dimg.cols; j++)
			{
				
				double nd=0;						//nd����������G*D��ֵ
				for (int kk = 0; kk < 2 * k + 1; kk++)
				{
					for (int jj = 0; jj < 2 * k + 1; jj++)
					{	
																	
						int ni = i +k-kk;			//����ÿ�����ص�ӳ��������
						int nj=j+k-jj;
						
						if (ni < 0)					//�߽������ȡ����
							ni = -ni;
						if (ni > dimg3.rows-1)
							ni = dimg3.rows-1-(ni-dimg3.rows+1);						
						if (nj < 0)
							nj = -nj;
						if (nj > dimg3.cols-1)
							nj = dimg3.cols-1-(nj-dimg3.cols+1);
						uchar ndij = dimg.at<uchar>(ni, nj);	
						nd += (m[kk][jj] * ndij);		//������
							
					}
				}
				omg.at<uchar>(i, j) = (uchar)nd;
			}
		}
		cout <<"Komplete!"<< endl;

		String s5 = "imgs/" + pics[ii] + "_new.bmp";
		imwrite(s5, omg);				//��Ϊ���Ὣ��ͨ��ͼתΪ��ͨ��ͼ����˲��ñȽ�����										//
		omg = imread(s5);				//�뵽����д�뵥ͨ��ͼ������Ϊ��ͨ��ͼ��ȡ
										//�ڴ���ͼƬ����ʱ������ΪӲ�̶�д��ʧЧ��
		//GaussianBlur(dimg, omg, Size(13, 13), 0, 0);
		//imshow("gauss", omg);


		//���ͼ��
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