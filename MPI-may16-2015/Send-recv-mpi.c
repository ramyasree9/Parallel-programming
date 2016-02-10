#include<stdio.h>
#define buffersize 100
#include "mpi.h"

int main(int argc ,char *argv[])
{
	int np,rank,msg;
	char buffer[buffersize];
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	if(rank==0)
	{
		sprintf(buffer,"hello world");
	//	msg=10;
	//	printf("processor %d is in send loop ",rank);	
		MPI_Send(buffer,buffersize,MPI_CHAR,1,0,MPI_COMM_WORLD);
	//	printf("process  %d sends msg: %d ",rank,msg);	
		printf("process  %d sends msg: %s ",rank,buffer);
	}
	else if(rank==1)
	{
		char temp_msg[buffersize];
	//	printf("processor %d is in recv loop ",rank);
		MPI_Recv(temp_msg,buffersize,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
	//	printf("msg: %d is received by  %d process",msg,rank);
		printf("msg: %s is received by  %d process",temp_msg,rank);
	}
	MPI_Finalize();
}
