#include <iostream>
#include <ctime>
//#include <Windows.h>
using namespace std;
#include "Strassen.h"
#define N 256
/*int main()
{
	Strassen_class<int> stra;
	int MatrixSize = N;

	int** MatrixA;    //����A
	int** MatrixB;    //����B
	int** MatrixC;    //�������

	clock_t start1;
	clock_t end1;

	clock_t start2;
	clock_t end2;

	//�����ڴ�
	MatrixA = new int *[MatrixSize];
	MatrixB = new int *[MatrixSize];
	MatrixC = new int *[MatrixSize];

	for (int i = 0; i < MatrixSize; i++)
	{
		MatrixA[i] = new int[MatrixSize];
		MatrixB[i] = new int[MatrixSize];
		MatrixC[i] = new int[MatrixSize];
	}

	stra.FillMatrix(MatrixA, MatrixB, MatrixSize);  //����ֵ

  //*******************conventional multiplication test
	start1 = clock();

	stra.MUL(MatrixA, MatrixB, MatrixC, MatrixSize);//��ͨ��������㷨 T(n) = O(n^3)

	end1 = clock();

	cout << "\n����������... \n";
	//stra.PrintMatrix(MatrixC, MatrixSize);

	//*******************Strassen multiplication test
	start2 = clock();

	stra.Strassen(N, MatrixA, MatrixB, MatrixC); //strassen��������㷨

	end2 = clock();


	cout << "\n����������... \n";
	//stra.PrintMatrix(MatrixC, MatrixSize);

	cout << "\n��ͨ����˷�: " << (double)(end1 - start1) / CLOCKS_PER_SEC << " s";
	cout << "\nStrassen�㷨:" << (double)(end2 - start2) / CLOCKS_PER_SEC << " s";
	system("Pause");
	return 0;

}*/
