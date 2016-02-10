#include<stdio.h>
#include "mpi.h"
int main(int argc,char *argv[])
{
	int np,pid;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&pid);
	printf("hello");
	printf("No of processes = %d,process id =%d \n ",np,pid );
  	MPI_Finalize();
	return 0;
}
