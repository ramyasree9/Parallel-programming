#include<stdio.h>
#include<mpi.h>

int main(int argc ,char *argv[])
{
	int np,rank;
	int i;
	struct Data
	{
		int a;
		float b[2];
		char  c;
	};
	struct Data input,output ;
	int block_length[3];
	MPI_Datatype new_type;
	MPI_Aint displacement[3];
	MPI_Datatype type_list[3];
	MPI_Aint address,start_address;
	MPI_Status status;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	
	block_length[0]=1;
	block_length[1]=2;
	block_length[2]=1;
	
	type_list[0]=MPI_INT;
	type_list[1]=MPI_FLOAT;
	type_list[2]=MPI_CHAR;

	MPI_Address(&input.a,&start_address);
	MPI_Address(&input.b,&address);
	displacement[0]=0;
	displacement[1]=address-start_address;
	MPI_Address(&input.c,&address);
	displacement[2]=address-start_address;
	
	MPI_Type_struct(3,block_length,displacement,type_list,&new_type);
	MPI_Type_commit(&new_type);
	if(rank==0)
	{
		printf("enter integer of data");
		scanf("%d",&input.a);
		printf("enter float values\n");
		for(i=0;i<2;i++)
		{
			scanf("%f",&input.b[i]);
		}
		getchar();	
		printf("enter char value\n");
		scanf("%c",&input.c);
		MPI_Send(&input,1,new_type,1,0,MPI_COMM_WORLD);

	}
	if(rank==1)
	{
		MPI_Recv(&output,1,new_type,0,0,MPI_COMM_WORLD,&status);
		printf("data received\n");
		printf("%d\n%f\n%f\n%c",output.a,output.b[0],output.b[1],output.c);
	}
	MPI_Type_free(&new_type);
	MPI_Finalize();
}
