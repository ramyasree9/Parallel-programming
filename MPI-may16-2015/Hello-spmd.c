#include<stdio.h>
#include "mpi.h"
#define buffersize 100
int main(int argc,char *argv[])
{
	int np,rank,iproc;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	
	if(rank==0)
	{
		char Send_msg[buffersize];
		sprintf(Send_msg,"hello world");
		for(iproc=1;iproc<np;iproc++)
		MPI_Send(Send_msg,buffersize,MPI_CHAR,iproc,0,MPI_COMM_WORLD);
	}
	else
	{
		char Recv_msg[buffersize];
		MPI_Recv(Recv_msg,buffersize,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
		printf(" process %d received msg: %s from process 0/n",rank,Recv_msg);
	}
}
