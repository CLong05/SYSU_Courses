#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<omp.h>
using namespace std;

int row_size, col_size, num;
typedef vector<double> Vector;
//����ѹ����ʽ�������
vector<double> val;//��СΪnum����ֵ
vector<int> col_idx;//��СΪnum�����Ӧֵ����ֵ
vector<int> row_ptr;//��СΪ��������ÿһ�е�һ������Ԫ����val�е�����
int thread_num;

Vector mul(Vector& vec)
{
	Vector result(row_ptr.size(),0);
#pragma omp parallel for num_threads(thread_num)//���У������˲����߳���
	for (int i = 0; i < row_ptr.size(); i++)
	{
		int end;
		/*if (i != row_ptr.size() - 1)
		{
			int j = i + 1;//��һ���з���Ԫ�ص��е��±�
			while (j < row_ptr.size())
			{
				if (row_ptr[j] != 0)
					break;
				j++;
			}
			if (j != row_ptr.size())
				end = row_ptr[j] - 1;
			else
				end = num - 1;
		}
		else
			end = num - 1;*/
		end = i == row_ptr.size() - 1 ? num - 1 : row_ptr[i + 1] - 1;
		for (int m = row_ptr[i]; m <= end; m++)
		{
			result[i] += val[m] * vec[col_idx[m]];//���еķ���ֵ��vec�Ķ�Ӧ��Ԫֵ��ˣ��ۼ�
		}
	}
	return result;
}

int main()
{
	ifstream fin("1138_bus.mtx");
	if (!fin)
	{
		cout << "���ļ�ʧ�ܣ�" << endl;
		exit(1);
	}
	while (fin.peek() == '%')
		while (fin.get() != '\n') ;//������������ǰ���ע��
	//��ȡ����������������ֵ�Ĵ�С
	fin >> row_size >> col_size >> num;
	val.resize(num);
	col_idx.resize(num);
	row_ptr.resize(row_size,0);
	
	Vector vec(col_size);
	int x, y;//x=��,y=��
	double t;//Ԫ��ֵ
	int former = -1;
	for (int i = 0; i < num; i++)
	{
		fin >> y >> x >> t;//��ȡÿһ����Ԫ���ҵ�һ���������У��ڶ�����������
		if ((x - 1) != former)
		{
			row_ptr[x - 1] = i;//��x�еķ���Ԫ����i��ʼ��
			former = x - 1;
		}	
		val[i] = t;
		col_idx[i] = y-1;
	}
	for (int i = 0; i < col_size; i++)
	{
		vec[i] = rand()%100+1;
	}
	cout << "�����벢�е��߳�����";
	cin >> thread_num;
	clock_t start = clock();
	Vector result;
	for(int i=0;i<1e4;i++)
		result = mul(vec);
	clock_t end = clock();
	cout << thread_num<<"���̲߳���ʱ��(s)��" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	for (auto i:result)
		cout << i << endl;
	system("pause");
	return 0;
}