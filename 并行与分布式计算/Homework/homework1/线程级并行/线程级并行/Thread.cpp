#include <immintrin.h>
#include <stdio.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
using namespace std;

const int N = 1000000;
const int num_of_CPUs = 4;//ȫ�ֱ�������
const int num_of_CPUs1 = 6;
const int num_of_CPUs2 = 8;
int *result1 = new int[N]();//��ÿ����Ԫ��ʼ��Ϊ0�����߳�
int *result3 = new int[N]();//����

struct ThreadParam {
	size_t begin;
	size_t end;
	int *result;//�������
	int *a;//����1
	int *b;//����2
	ThreadParam(size_t begin1, size_t end1, int *result1, int *a1, int *b1) :begin(begin1), end(end1), result(result1), a(a1), b(b1) {}
};

DWORD WINAPI addvalues2(LPVOID param) {
	ThreadParam*p = static_cast<ThreadParam*>(param);//�����param��void*������Ҫ����ת��
	for (size_t i = p->begin; i < p->end; ++i)
	{
		p->result[i] = p->a[i] + p->b[i];
		if (i % 100 == 0)
			Sleep(10);
	}
	delete p;
	return 0;
}

void addvalues3(int *a, int *b, int *&result)
{
	for (int i = 0; i < N; i++)
	{
		result[i] = a[i] + b[i];
		if (i % 100 == 0)//��������100���󣬳�˯0.01s
			Sleep(10);
	}
}


int main()
{
	HANDLE Threads[num_of_CPUs];
	int a[N];
	int b[N];
	for (int i = 0; i < N; i++)//�����������ʼ������
	{
		a[i] = rand() % 100 + 1;
		b[i] = rand() % 100 + 1;
	}

	clock_t start1 = clock();//����ο�ʼǰȡ��ϵͳ����ʱ��(s)  

	for (int i = 0; i < num_of_CPUs; ++i)
	{
		ThreadParam* p = new ThreadParam(i*N / num_of_CPUs, (i + 1)*N / num_of_CPUs, result1, a, b);
		//�ڲ�������ʱ���Ѻ���Ķ������
		if (i == num_of_CPUs - 1)
			p->end = N - 1;
		Threads[i] = CreateThread(NULL, 0, addvalues2, p, 0, NULL);
	}
	WaitForMultipleObjects(num_of_CPUs, Threads, true, INFINITE);
	clock_t end1 = clock();//����ν�����ȡ��ϵͳ����ʱ��(s)  

	
	/*clock_t start2 = clock();
	for (int i = 0; i < num_of_CPUs1; ++i)
	{
		ThreadParam* p = new ThreadParam(i*N / num_of_CPUs1, (i + 1)*N / num_of_CPUs1, result1, a, b);
		if (i == num_of_CPUs1 - 1)
			p->end = N - 1;//�ڲ�������ʱ���Ѻ���Ķ������
		Threads[i] = CreateThread(NULL, 0, addvalues2, p, 0, NULL);
	}
	WaitForMultipleObjects(num_of_CPUs1, Threads, true, INFINITE);
	clock_t end2 = clock();

	clock_t start4 = clock();
	for (int i = 0; i < num_of_CPUs2; ++i)
	{
		ThreadParam* p = new ThreadParam(i*N / num_of_CPUs2, (i + 1)*N / num_of_CPUs2, result1, a, b);
		//�ڲ�������ʱ���Ѻ���Ķ��������
		if (i == num_of_CPUs2 - 1)
			p->end = N - 1;
		Threads[i] = CreateThread(NULL, 0, addvalues2, p, 0, NULL);
	}
	WaitForMultipleObjects(num_of_CPUs2, Threads, true, INFINITE);
	clock_t end4 = clock();*/

	clock_t start3 = clock();
	addvalues3(a, b, result3);
	clock_t end3 = clock();
	cout << "4���̼߳�����ʱ��(s)��" << (double)(end1 - start1) / CLOCKS_PER_SEC << endl;
	//cout << "6���̼߳�����ʱ��(s)��" << (double)(end2 - start2) / CLOCKS_PER_SEC << endl;
	//cout << "8���̼߳�����ʱ��(s)��" << (double)(end4 - start4) / CLOCKS_PER_SEC << endl;
	cout << "��ͨ����ʱ��(s)��" << (double)(end3 - start3) / CLOCKS_PER_SEC << endl;

	cout << "4�����ٱ�Ϊ" << (double)(end3 - start3) / (double)(end1 - start1)<<endl;
	//cout << "6�����ٱ�Ϊ" << (double)(end3 - start3) / (double)(end2 - start2) << endl;
	//cout << "8�����ٱ�Ϊ" << (double)(end3 - start3) / (double)(end4 - start4) << endl;
	system("pause");
	return 0;
}
