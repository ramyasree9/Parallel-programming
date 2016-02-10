#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
	int i,File_size=10,buffer_size=10;
	char buffer[buffer_size],filename[20];
	int np,rank;
	MPI_File fp;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	for(i=0;i<10;i++)
	{
		buffer[i]=rank+48;
	}
	sprintf(filename,"file%d",rank);
	MPI_File_open(MPI_COMM_SELF,filename,MPI_MODE_RDWR|MPI_MODE_CREATE,MPI_INFO_NULL,&fp);
	MPI_File_write(fp,buffer,buffer_size,MPI_CHAR,&status);
	printf("%d %s\n ",rank,buffer);
	MPI_File_close(&fp);
	MPI_Finalize();
	
}
