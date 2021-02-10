#include <mpi.h>  
#include <stdio.h> 
#include<memory.h>
#include <stdlib.h>
#include<time.h>
#define MAX 100000000

int main(int argc,char* argv[]) {
	int my_rank;
	MPI_Status status;
	double timesend = 0;
	double timerecv = 0;
    int* buffsend = (int*)malloc(MAX*sizeof(int));
    int* buffrecv = (int*)malloc(MAX*sizeof(int));
 	memset(buffsend, 5, MAX);
	memset(buffrecv, 0, MAX);

	MPI_Init(&argc, &argv);//MPI��ʼ�� 
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);//��ȡ���̱��
	if (my_rank == 0) {
		double timerecv_in_1 = 0;
		double duration1 = 0;// = timerecv_in_1 - timesend;
		timesend = MPI_Wtime();/*��ȡʱ��*/
		MPI_Send(buffsend, MAX, MPI_INT, 1, 0, MPI_COMM_WORLD);
		
		MPI_Recv(&timerecv_in_1, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, &status);
		duration1 = timerecv_in_1 - timesend;
		printf("4�����ֽڵ�ͨ��ʱ�� :  %lf s\n", duration1);
		printf("���� �� %lf Mbps\n", 8*100 * sizeof(MPI_INT) / duration1);
	}
	else if (my_rank == 1) {
		MPI_Recv(buffrecv, MAX, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		timerecv = MPI_Wtime();
		MPI_Send(&timerecv, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);/*�ѽ���ʱ�䴫��ȥ*/
	}

	MPI_Finalize();
	return 0;
}
