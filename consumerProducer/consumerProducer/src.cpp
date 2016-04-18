
#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define BSIZE 4
#define TABLESIZE 8
char chTable[TABLESIZE] = {'M','O','H','T','V','E','X','N'};

//���ÿ���̨�����ɫ
BOOL SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;
	return SetConsoleTextAttribute(hConsole, wAttributes);
}
const int END_PRODUCE_NUMBER = 4;   //������Ʒ����
const int END_CONSUME_NUMBER = 3;	//���Ѳ�Ʒ����
int nextin = 0;
int nextout = 0;
char g_Buffer[BSIZE] = {'$','$','$','$'};                        //������
//�¼���ؼ���
CRITICAL_SECTION g_cs;	//�����ٽ���ʵ�ֻ���
HANDLE semaphoreBufferEmpty, semaphoreBufferFull;
//�������̺߳���
unsigned int __stdcall ProducerThreadFun(PVOID pM)
{
	srand((unsigned)time(NULL)+GetCurrentThreadId());
	Sleep((rand()) % 5000);
	
	char item;
	for (int i = 0; i < END_PRODUCE_NUMBER; i++)
	{
		Sleep(rand() % 5000);
		//�ȴ�������Ϊ��
		WaitForSingleObject(semaphoreBufferEmpty, INFINITE);

		//����ķ��ʻ�����
		EnterCriticalSection(&g_cs);
		item = chTable[rand() % TABLESIZE];
		g_Buffer[nextin++] = item;
		nextin = nextin%BSIZE;
		printf("������%d������%c���뻺����\n", GetCurrentThreadId(),item);
		for (int j = 0; j < BSIZE; j++)
			printf("%c ", g_Buffer[j]);
		printf("\n");
		LeaveCriticalSection(&g_cs);

		//֪ͨ����������������
		ReleaseSemaphore(semaphoreBufferFull, 1, NULL);
	}
	return 0;
}
//�������̺߳���
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
		//�ȴ���������������
		WaitForSingleObject(semaphoreBufferFull, INFINITE);

		//����ķ��ʻ�����
		EnterCriticalSection(&g_cs);
		int currentout = nextout;
		item = g_Buffer[nextout++];
		nextout = nextout%BSIZE;

		g_Buffer[currentout] = '$';
		printf("  ������%d�ӻ�������ȡ����%c\n",GetCurrentThreadId(), item);
		for (int j = 0; j < BSIZE; j++)
			printf("%c ", g_Buffer[j]);
		printf("\n");
		LeaveCriticalSection(&g_cs);

		//֪ͨ��������Ϊ��
		ReleaseSemaphore(semaphoreBufferEmpty, 1, NULL);

		Sleep(10); //some other work should to do
	}
	return 0;
}
int main()
{
	int i;
	srand((unsigned)time(NULL));	


	InitializeCriticalSection(&g_cs);	//��ʼ���ٽ���
	//���������Զ���λ�¼���һ����ʾ�������Ƿ�Ϊ�գ���һ����ʾ�������Ƿ��Ѿ�����
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

	//�����¼��͹ؼ���
	CloseHandle(semaphoreBufferEmpty);
	CloseHandle(semaphoreBufferFull);
	DeleteCriticalSection(&g_cs);
	return 0;
}