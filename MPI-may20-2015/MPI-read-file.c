#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

int main(int argc,char *argv[])
{	
	MPI_Offset Filesize;
	MPI_Status status;
	int buffer_size;
	int np,rank;
	char buffer[buffer_size+1];
	MPI_File fp;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_File_open(MPI_COMM_WORLD,"Myfile",MPI_MODE_RDONLY,MPI_INFO_NULL,&fp);
	MPI_File_get_size(fp,&Filesize);
	buffer_size=Filesize/(np*sizeof(char));
	MPI_File_read_at(fp,rank*buffer_size*(sizeof(char)),buffer,buffer_size,MPI_CHAR,&status);
	buffer[buffer_size]='\0';
	printf("read by process: %d  %s\n",rank,buffer);
	MPI_File_close(&fp);
	MPI_Finalize();
}
