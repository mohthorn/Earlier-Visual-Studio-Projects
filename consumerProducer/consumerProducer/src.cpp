
#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define BSIZE 4
#define TABLESIZE 8
char chTable[TABLESIZE] = {'M','O','H','T','V','E','X','N'};

//设置控制台输出颜色
BOOL SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;
	return SetConsoleTextAttribute(hConsole, wAttributes);
}
const int END_PRODUCE_NUMBER = 4;   //生产产品个数
const int END_CONSUME_NUMBER = 3;	//消费产品个数
int nextin = 0;
int nextout = 0;
char g_Buffer[BSIZE] = {'$','$','$','$'};                        //缓冲区
//事件与关键段
CRITICAL_SECTION g_cs;	//定义临界区实现互斥
HANDLE semaphoreBufferEmpty, semaphoreBufferFull;
//生产者线程函数
unsigned int __stdcall ProducerThreadFun(PVOID pM)
{
	srand((unsigned)time(NULL)+GetCurrentThreadId());
	Sleep((rand()) % 5000);
	
	char item;
	for (int i = 0; i < END_PRODUCE_NUMBER; i++)
	{
		Sleep(rand() % 5000);
		//等待缓冲区为空
		WaitForSingleObject(semaphoreBufferEmpty, INFINITE);

		//互斥的访问缓冲区
		EnterCriticalSection(&g_cs);
		item = chTable[rand() % TABLESIZE];
		g_Buffer[nextin++] = item;
		nextin = nextin%BSIZE;
		printf("生产者%d将数据%c放入缓冲区\n", GetCurrentThreadId(),item);
		for (int j = 0; j < BSIZE; j++)
			printf("%c ", g_Buffer[j]);
		printf("\n");
		LeaveCriticalSection(&g_cs);

		//通知缓冲区有新数据了
		ReleaseSemaphore(semaphoreBufferFull, 1, NULL);
	}
	return 0;
}
//消费者线程函数
unsigned int __stdcall ConsumerThreadFun(PVOID pM)
{
	srand((unsigned)time(NULL) + GetCurrentThreadId());
	Sleep((rand()) % 5000);
	int i;
	char item;
//	volatile bool flag = true;
	for (i = 0; i < END_CONSUME_NUMBER;i++)
	{
		Sleep(rand() % 5000);
		//等待缓冲区中有数据
		WaitForSingleObject(semaphoreBufferFull, INFINITE);

		//互斥的访问缓冲区
		EnterCriticalSection(&g_cs);
		int currentout = nextout;
		item = g_Buffer[nextout++];
		nextout = nextout%BSIZE;

		g_Buffer[currentout] = '$';
		printf("  消费者%d从缓冲区中取数据%c\n",GetCurrentThreadId(), item);
		for (int j = 0; j < BSIZE; j++)
			printf("%c ", g_Buffer[j]);
		printf("\n");
		LeaveCriticalSection(&g_cs);

		//通知缓冲区已为空
		ReleaseSemaphore(semaphoreBufferEmpty, 1, NULL);

		Sleep(10); //some other work should to do
	}
	return 0;
}
int main()
{
	int i;
	srand((unsigned)time(NULL));	


	InitializeCriticalSection(&g_cs);	//初始化临界区
	//创建二个自动复位事件，一个表示缓冲区是否为空，另一个表示缓冲区是否已经处理
	semaphoreBufferEmpty = CreateSemaphore(NULL, 4, 4, NULL);
	semaphoreBufferFull = CreateSemaphore(NULL, 0, 4, NULL);


	const int THREADNUM = 7;
	HANDLE hThread[THREADNUM];
	for (i = 0; i < 3; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ProducerThreadFun, NULL, 0, NULL);
	}
	for (i = 3; i < 7; i++)
	{
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
	}
	WaitForMultipleObjects(THREADNUM, hThread, TRUE, INFINITE);
	for (i = 0; i < 7;i++)
		CloseHandle(hThread[i]);

	//销毁事件和关键段
	CloseHandle(semaphoreBufferEmpty);
	CloseHandle(semaphoreBufferFull);
	DeleteCriticalSection(&g_cs);
	return 0;
}