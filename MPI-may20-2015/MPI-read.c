#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>
#define File_size 16
int main(int argc,char *argv[])
{
	int	np,Rank,i;
	int	*Buffer,Buffer_size;
	MPI_Status	status;
	MPI_File	 Fp;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&Rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
//	Buffer_size	= (File_size)/np;
	Buffer_size=1;
	Buffer	=(int *)malloc(Buffer_size*(sizeof(int)));
	MPI_File_open(MPI_COMM_WORLD,"Readfile",MPI_MODE_RDONLY,MPI_INFO_NULL,&Fp);
	MPI_File_read_at(Fp,0,Buffer,Buffer_size,MPI_INT,&status);
	printf("process: %d read \n",Rank);
	for(i=0;i<Buffer_size;i++)
	{
		printf("%d\n",Buffer[i]);
	}
	MPI_File_close(&Fp);
	MPI_Finalize();
		
}
