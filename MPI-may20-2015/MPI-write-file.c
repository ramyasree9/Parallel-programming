#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
	int np,rank;
	MPI_File np;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COM_WORLD,&rank);
	MPI_File_open(MPI_COMM_WORLD,"writefile",);
	MPI_Fianlize();
}
