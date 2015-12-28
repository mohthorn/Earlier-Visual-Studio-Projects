// reading a text file  
#include <iostream>  
#include <fstream>  
#include<TCHAR.H>
#include <stdlib.h>  
using namespace std;
int main() {
	char buffer[256];
	char output[1000];
	ifstream in("ina.txt");
	ofstream out("ans.txt");
	in.getline(buffer, 100);
	int len;
	int m=3;
	len = strlen(buffer);
	//cin >> m;
	int tail = 0;
	for (int i = 0; i < len; i++)
	{
		
		int n;
		n = len - i;
		if (n == 1)
		{
			tail++;
			output[tail] = 0;
			out << output<<" "<<buffer[len-1]<<endl;
			return 0;
		}
		else
		{
			int inl;
			inl = n ? m : n < m;
			int max = inl;
			if (1)
			{
				int j=0;
				while(max>0)
				{
					
					if (buffer[i +j] < 0)
					{
						output[tail] = buffer[i +  j];
						output[++tail] = buffer[i+j+1];
						tail++;
						j += 2;

					}
					else
					{
						output[tail] = buffer[i + j];
						tail++;
						j += 1;
						
					}
					max -= 1;

				}
				i = i+j-1;
				output[tail++] = ' ';
				//tail += inl;
			}

			}
		

	}
	tail++;
	output[tail] = 0;
	out << output << " " << buffer[len - 1] << endl;
	

	return 0;
}