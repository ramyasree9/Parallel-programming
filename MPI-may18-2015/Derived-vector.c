#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
	int np,rank,i,j;
	int arr[10][10];
	MPI_Status status;
	MPI_Datatype new_type;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Type_vector(10,1,10,MPI_INT,&new_type);	
	MPI_Type_commit(&new_type);
	if(rank==0)
	{
		for(i=0;i<10;i++)
		{
			for(j=0;j<10;j++)
			{
				arr[i][j]=i+1;
			}
		}
		MPI_Send(&arr[0][4],1,new_type,1,0,MPI_COMM_WORLD);
	}
	if(rank==1)
	{
		MPI_Recv(&arr[0][1],1,new_type,0,0,MPI_COMM_WORLD,&status);
		for(i=0;i<10;i++)
		{
			for(j=0;j<10;j++)
			{
				printf("%d ",arr[i][j]);
			}
			printf("\n");
		}

	}

	MPI_Type_free(&new_type);
	MPI_Finalize();
}
