#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
	int np,rank,i,arr[10];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Datatype new_type;
	MPI_Type_contiguous(5,MPI_INT,&new_type);
	MPI_Type_commit(&new_type);
	if(rank==0)
	{
		for(i=0;i<10;i++)
		arr[i]=i+1;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&arr[5],1,new_type,0,MPI_COMM_WORLD);
	if(rank==1)
	{
		for(i=0;i<10;i++)
		printf("%d\n",arr[i]);
	}
	MPI_Type_free(&new_type);
	MPI_Finalize();
	
}
