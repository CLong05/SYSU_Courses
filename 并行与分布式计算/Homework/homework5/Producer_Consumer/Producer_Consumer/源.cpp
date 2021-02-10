#include<iostream>
#include<time.h>
#include"MutliAccessQueue.h"

using namespace std;
MultiAccessQueue<int> q;
void producer(int cnt)//ÿ��������cnt������
{
	for (int i = 0; i < cnt; ++i)
		q.push(i);
}
void consumer(int cnt)
{
	for (int i = 0; i < cnt; ++i)
		q.pop();
}

int main()
{
	int num = 0;
	cout << "������������-�����ߵ�������";
	cin >> num;
	omp_init_lock(&(q.back_mutex));
	omp_init_lock(&(q.front_mutex));
	clock_t start = clock();
	omp_set_num_threads(omp_get_num_procs());//�����߳���
#pragma omp parallel for
	for (int i = 0; i < num; ++i)//��������������߲���
	{
		int thread_id = omp_get_thread_num();
		if (thread_id < omp_get_num_threads() / 2)
			producer(250);
		else
			consumer(250);
	}
	clock_t end = clock();
	//cout << q.cnt << endl;
	cout <<num<<"��������-�����ߵ�ʱ��Ϊ��(s)"<< (double)(end - start) / CLOCKS_PER_SEC << endl;
	omp_destroy_lock(&(q.front_mutex));
	omp_destroy_lock(&(q.back_mutex));
	return 0;
}
