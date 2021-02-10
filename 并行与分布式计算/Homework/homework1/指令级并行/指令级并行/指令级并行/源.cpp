#include <immintrin.h>
#include <stdio.h>
#include<iostream>
#include<time.h>
#include<vector>
#include<Windows.h>
using namespace std;
const int N = 1000000;
int *result2 = new int[N]();//��ÿ����Ԫ��ʼ��Ϊ0�����߳�
int *result3 = new int[N]();//����
//�����ӣ����ܷ���int*,��Ϊ��ʱ��������������
void addvalues1(int *a, int *b, int *&result)//��֪sizeΪ1000 000
{
	int nBlockWidth = 8;//ÿ�μ���8��int���������
	int cntBlock = N / 8;//block������ѭ���������ޣ�
	__m256i loadData1, loadData2;
	__m256i resultData = _mm256_setzero_si256();
	__m256i *p1 = (__m256i *)a;//����ָ�����͵�ת��
	__m256i *p2 = (__m256i *)b;
	__m256i *p3 = (__m256i *)result;
	for (int i = 0; i < cntBlock; i++)
	{
		loadData1 = _mm256_load_si256(p1);//��������1
		loadData2 = _mm256_load_si256(p2);//��������2
		resultData = _mm256_add_epi32(loadData1, loadData2);//��2�������
		_mm256_store_si256(p3, resultData);//ж�����ݻؽ������result
		p1 += 1;//�������Ǽ�1�����Ǽ�8����p1+1=p1+1*8 int,"1"means one __m256i)
		p2 += 1;
		p3 += 1;
		//if (i % 125 == 0)
			//Sleep(100);
	}
	//128��256�Ĳ�ͬ�����ڰѺ���ǰ���256��ɾ���������256�ĳ�128
	/*int nBlockWidth = 4;//ÿ�μ���8��int���������
	int cntBlock = N / 4;//block������ѭ���������ޣ�
	__m128i loadData1, loadData2, resultData;
	//__m128i resultData = _mm128_setzero_si128();
	__m128i *p1 = (__m128i *)a;//����ָ�����͵�ת��
	__m128i *p2 = (__m128i *)b;
	__m128i *p3 = (__m128i *)result;
	for (int i = 0; i < cntBlock; i++)
	{
		loadData1 = _mm_load_si128(p1);//��������1
		loadData2 = _mm_load_si128(p2);//��������2
		resultData = _mm_add_epi32(loadData1, loadData2);//��2�������
		_mm_store_si128(p3, resultData);//ж�����ݻؽ������result
		p1 += 1;//�������Ǽ�1�����Ǽ�8����p1+1=p1+1*8 int,"1"means one __m256i)
		p2 += 1;
		p3 += 1;
		if (i % 25 == 0)
			Sleep(1);
	}*/
	return;
}

void addvalues3(int *a, int *b, int *&result)
{
	for (int i = 0; i < N; i++)
	{
		result[i] = a[i] + b[i];
		//if (i % 1000 == 0)
			//Sleep(100);
	}
}

int main()
{
	
	int a[N];
	int b[N];
	for (int i = 0; i < N; i++)
	{
		a[i] = rand() % 100 + 1;
		b[i] = rand() % 100 + 1;
	}

	clock_t start2 = clock();
	addvalues1(a, b, result2);
	clock_t end2 = clock();

	clock_t start3 = clock();
	addvalues3(a, b, result3);
	clock_t end3 = clock();

	cout << "ָ�����ʱ��(s)��" << (double)(end2 - start2) / CLOCKS_PER_SEC << endl;
	cout << "��ͨ����ʱ��(s)��" << (double)(end3 - start3) / CLOCKS_PER_SEC << endl;
	cout << "���ٱ�Ϊ" << (double)(end3 - start3) / (double)(end2 - start2) << endl;
	system("pause");
	return 0;
}
