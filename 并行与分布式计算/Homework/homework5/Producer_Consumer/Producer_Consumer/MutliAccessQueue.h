#pragma once
#include<queue>
#include<iostream>
#include<omp.h>
using namespace std;
template<class T>
class MultiAccessQueue :queue<T>//�̳�queue
{	
public:
	omp_lock_t back_mutex;//push����
	omp_lock_t front_mutex;//pop����
	int cnt = 0;
	void push(T val)
	{
		omp_set_lock(&back_mutex);//�����
		queue<T>::push(val);
		omp_unset_lock(&back_mutex);
		return;
	}
	void pop()
	{
		omp_set_lock(&front_mutex);//��Ҫ�������棬������ܻ����
		//while (queue<T>::empty());
		if (!queue<T>::empty())
		{
			queue<T>::pop();
			//cnt++;
		}
			
		omp_unset_lock(&front_mutex);
		return;
	}
};
