#include<iostream>
#include <ctime>
#include<fstream>
using namespace std;
#define MAPSIZE 8
#define CHESS_BLACK 1
#define CHESS_WHITE 2
#define N1 6
#define N2 64
#define count 100
#define AvaNum 100


//char b[100][100] = { 0 };
//char convert[3] = { 'b','e','w' };
//void drawBoard(int size=8)
//{
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			cout << convert[b[i][j] + 1] << "  ";
//		}
//		cout << endl;
//	}
//}
//
//int main()
//{
//	while (1)
//	{
//		int input;
//		char renew;
//		cin >> input;
//		drawBoard(8);
//		getchar();
//		getchar();
//		system("cls");
//	}
//	return 0;
//}

class Ava {
public: int weight1[N1][N2];
		int weight2[N1];
		int ThresholdFunc()
		{

		}
		int Evalue()
		{

		}
		Ava()
		{

		}
};



/************************************************/\

typedef struct wstruct {
	int score;
	double pos;
	int size;
	double w[400];
}WS;

void init(WS (&ws)[AvaNum]) {				//初始化
	srand((unsigned)time(0));
	for (int i = 0; i < AvaNum; i++)
	{
		ws[i].size = N2 * N1 + N1;
		for (int j = 0; j < ws[i].size; j++) 
		{
			
			ws[i].w[j]= 0.4 * rand() / RAND_MAX - 0.2;
			
			//cout << ws[i].w[j]<< " ";
		}
		//cout << endl;
	}
}


double getRand(double in);
int getRand(int in);

WS recombine(WS a,WS b)			//重组
{
	WS result;
	int mPoint= getRand(a.size-1);
	result.size = a.size; 
	result.score = (a.score + b.score) / 2;			//分数取均值
	for (int i = 0; i < mPoint; i++)
	{
		result.w[i] = a.w[i];
		
	}
	for (int i = mPoint; i < a.size; i++)
	{
		result.w[i] = b.w[i];
	}
	return result;
}

void mutant(WS &a)				//突变
{
	int p1 = getRand(a.size-1);
	int p2 = getRand(a.size-1);
	swap(a.w[p1], a.w[p2]);
}

double getRand(double in=1.0)			//随机函数
{
	return fabs(in*2.0 * rand() / RAND_MAX - in);
}
int getRand(int in = 1)
{
	return rand()%in;
}


void Fight(Ava First, Ava Second, int(&value)[AvaNum], int i, int j);

void EvolutionaryComputing()
{
	int maxposition = 0;
	double pMutant = 0.1,pRecomb=1;
	ofstream out("out.txt");
	ofstream out2("superout.txt");
	WS ws[AvaNum];
	init(ws);
	Ava Avaarray[AvaNum] ;

	int value[AvaNum] = {0};
	for (int p = 0; p<count; p++)			//迭代次数
	{
		for (int i = 0; i < AvaNum; i++)
		{
			Ava TAva;					//将权值赋给Ava
			Avaarray[i] = TAva;
		}
		for (int i = 0; i<AvaNum - 1; i++)
		{
			for (int j = i + 1; j<AvaNum; j++)
			{
				Fight(Avaarray[i], Avaarray[j], value, i, j);
			}
		}
		int sum=0;									//归一化分母
		for (int i = 0; i < AvaNum; i++)
		{
			sum += value[i];
			ws[i].score = value[i];
		}
		double sumPos=0;
		for (int i = 0; i < AvaNum; i++)
		{
			sumPos +=(value[i]*1.0 / (double)sum);
			ws[i].pos = sumPos;
		}
		ws[AvaNum - 1].pos += 0.1;					//修正使最后一项的值大于0.1




		//选择
		int elite = AvaNum/2;
		WS wsE[AvaNum / 2];
		for (int i = 0; i < elite; i++)
		{
			double p = getRand(1.0);

			for (int j = 0; j < AvaNum; j++)			//ws中选取，可重复
			{
				if (p < ws[j].pos)
				{
					wsE[i] = ws[j];
					break;
				}
			}

		}
		for (int i = 0; i < elite; i++)				//复制回到ws
		{
			ws[i] = wsE[i];
		}
		//重组
		for (int i = 0; i < elite / 2; i++)			//elite/2次重组，生成elite个子代
		{
			int a = getRand(elite-1);				//从elite中选取
			int b = getRand(elite-1);
			ws[2*i+elite]=recombine(ws[a],ws[b]);
			ws[2*i + elite + 1] = recombine(ws[b],ws[a]);

		}
		//突变
		for (int i = elite; i < AvaNum; i++)		//AvaNum-elite次突变
		{
			if (getRand(1.0) < pMutant)
			{
				//cout << "before"<<i << endl;
				//for (int j = 0; j < ws[i].size; j++)
				//	cout << ws[i].w[j];
				//cout << endl;
				mutant(ws[i]);
				//cout << "after" << endl;
				//for (int j = 0; j < ws[i].size; j++)
				//	cout << ws[i].w[j];
				//cout << endl;
			}

		}
		//输出过程
		cout << "generation"<<p<<endl;
		out << p << endl<<endl;
		maxposition = 0;
		for (int i = 0; i < AvaNum; i++)
		{
			out << "score:" << ws[i].score << endl;
			if (ws[i].score > ws[maxposition].score)
			{
				
				maxposition = i;
			}
			for (int j = 0; j < ws[i].size; j++)
			{
				out << ws[i].w[j]<<" ";				
			}
			out << endl;
		}


		
	}

	//输出结果
	out2 << ws[maxposition].score << endl;
	for (int i = 0; i < ws[maxposition].size; i++)
	{
		out2 << ws[maxposition].w[i] << " ";
	}
	//for (int i = 0; i < AvaNum; i++)
	//{
	//	cout << value[i] << " ";
	//}
	//把最优的神经网络写到文件里面去
}



/***************************************************/
void Fight(Ava First, Ava Second, int (&value)[AvaNum], int i, int j) //对Value更新
{
	
	value[i] = getRand(10);

	value[j] = getRand(10);
	//cout << value[i] << " " << value[j] << endl;
}



int Updatechess(int * chess, int x, int y)//下一个子更新棋盘状态，并判断胜负
{
	//如果返回1，代表当前下的这一方胜利
	//返回0，代表没分出胜负
	//返回-1，代表平局
	return 1;
}

int main() 
{
	EvolutionaryComputing();

	return 0;
}