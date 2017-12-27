
#include "mpi.h"  
#include "stdio.h"  
#include "string.h"  
#include "math.h"  
int isPrime(int n)
{
	int  flag = 1;
	for (int m = 2; m <= sqrt(n*1.0); m++)
	{
		if (n%m == 0)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}
int main(int argc, char *argv[])
{

	int a, mypid, sum = 0, local = 0, size;
	int flag;
	double starttime1, endtime1, starttime2, endtime2, t1, t2;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &mypid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (mypid == 0)
	{
		scanf_s("%d", &a);
	}
	MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);
	starttime1 = MPI_Wtime();
	for (int i = mypid * 2 + 1; i <= a; i += size * 2) //ÿ���������Լ������񣬱�����local��  
	{
		local += isPrime(i);

	}
	MPI_Reduce(&local, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);//���й�Լ�����ǰ����н��̵�local���������õ��ܵ���������  
	endtime1 = MPI_Wtime();
	t1 = endtime1 - starttime1;
	if (mypid == 0)
	{
		printf("����ʱ��=%f\n", t1);
		printf("�������������ǣ� %d\n", sum);
	}




	sum = 0;
	starttime2 = MPI_Wtime();
	if (mypid == 0)
	{

		for (int i = 1; i <= a; i += 2) //ÿ���������Լ������񣬱�����local��  
		{
			sum += isPrime(i);
		}
		endtime2 = MPI_Wtime();
		t2 = endtime2 - starttime2;
		printf("�������������ǣ� %d\n", sum);

		printf("����ʱ��=%f\n", t2);
	}
	MPI_Finalize();
	return 0;
}