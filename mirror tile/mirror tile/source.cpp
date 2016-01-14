#include<iostream>
using namespace std;

char b[100][100] = { 0 };
char convert[3] = { 'b','e','w' };
void drawBoard(int size=8)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << convert[b[i][j] + 1] << "  ";
		}
		cout << endl;
	}
}

int main()
{
	while (1)
	{
		int input;
		char renew;
		cin >> input;
		drawBoard(8);
		getchar();
		getchar();
		system("cls");
	}
	return 0;
}