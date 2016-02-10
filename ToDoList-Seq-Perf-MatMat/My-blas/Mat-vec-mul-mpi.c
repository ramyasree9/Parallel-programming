#include<stdio.h>
#include<stdlib.h>
#include "cblas.h"
#include<mpi.h>
int main(int argc,char *argv[])
{
 	int     Matrix_rows,Matrix_cols,Vector_size,Scatter_size;
	int	No_process,Myrank,Root=0; 
	int 	i,j,Index = 0;
	double  start,end,time_taken,*time_arr;
	double	**Matrix,*Vector;
	double	*My_final_vector,*Final_vector,*Mybuffer,*Buffer;
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&No_process);
	MPI_Comm_rank(MPI_COMM_WORLD,&Myrank);

	if(Myrank==0)
	{
		printf("enter no of rows and columns of matrix and size of vector");
		scanf("%d%d%d",&Matrix_rows,&Matrix_cols,&Vector_size);
		if(Matrix_rows<No_process)
		{
			printf("no of rows should be greater than or equal to no of processes");
			MPI_Finalize();
			exit(0);
		}
		if(Matrix_rows%No_process!=0)
		{
			printf("rows cant be partitioned among processes");
			MPI_Finalize();
			exit(0);
		}	
		if(Matrix_cols!=Vector_size)
		{
			printf("cant perform multiplication");
			MPI_Finalize();			
			exit(0);
		}
		Matrix	=(double **)malloc(Matrix_rows*(sizeof (double *)));
		if(Matrix==NULL)
		{
			printf("memory not available");
			MPI_Finalize();
			exit(0);
		}
		Vector	=(double *)malloc(Vector_size*(sizeof(double )));
		if(Vector==NULL)
		{		
			printf("memory not available ");
			MPI_Finalize();
			exit(0);
		}
		for(i=0;i<Matrix_rows;i++)
		{
			Matrix[i]=(double *)malloc(Matrix_cols*(sizeof(double )));
		}
		for(i=0;i<Matrix_rows;i++)
		{
			for(j=0;j<Matrix_cols;j++)
				{
					Matrix[i][j]	=(double) rand();
				}
		}
		for(i=0;i<Vector_size;i++)
		{	
			Vector[i]	=(double) rand();
		}
		/***convert 2d array to 1d***/
		Buffer	=(double *)malloc(Matrix_rows*Matrix_cols*(sizeof(double)));
		if(Buffer==NULL)
		{	
			printf("memory not available ");
			MPI_Finalize();
			exit(0);
		}
		for(i=0;i<Matrix_rows;i++)
		{
			for(j=0;j<Matrix_cols;j++)
			{
				Buffer[Index]=Matrix[i][j];
				Index++;
			}
		}
	}  /* MyRank ==0 Ends */ 
	start=MPI_Wtime();
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&Vector_size,1,MPI_INT,Root,MPI_COMM_WORLD);
	MPI_Bcast(&Matrix_rows,1,MPI_INT,Root,MPI_COMM_WORLD);
	MPI_Bcast(&Matrix_cols,1,MPI_INT,Root,MPI_COMM_WORLD);

	if(Myrank!=0)
	Vector	=(double *)malloc(Vector_size*(sizeof(double)));
	MPI_Bcast(Vector,Vector_size,MPI_DOUBLE,Root,MPI_COMM_WORLD);
	Scatter_size	=Matrix_rows/No_process;
	Mybuffer	=(double *)malloc(Scatter_size*Matrix_cols*(sizeof(double)));
	if(Mybuffer==NULL)
	{
		printf("memory not available ");
		MPI_Finalize();
	        exit(0);
	}
	MPI_Scatter(Buffer,Scatter_size*Matrix_cols,MPI_DOUBLE,Mybuffer,Scatter_size*Matrix_cols,MPI_DOUBLE,Root,MPI_COMM_WORLD);
	My_final_vector	=(double *)malloc(Scatter_size*(sizeof(double)));
	cblas_dgemv(CblasRowMajor,CblasNoTrans,Scatter_size,Matrix_cols,1,Mybuffer,Matrix_cols,Vector,1,0,My_final_vector,1);
	if(Myrank==0)
	{
		Final_vector	=(double *)malloc(Matrix_rows*(sizeof(double)));
	}
        MPI_Gather(My_final_vector,Scatter_size,MPI_DOUBLE,Final_vector,Scatter_size,MPI_DOUBLE,Root,MPI_COMM_WORLD);
	if(Myrank==0)
	{
		printf("final vector is \n");
		for(i=0;i<Matrix_rows;i++)
		{
			printf("%f\n",Final_vector[i]);
		}
	}
	end=MPI_Wtime();
	time_arr=(double *)malloc(No_process*sizeof(double));
	time_taken=end-start;
//	printf("time_taken by process: %d is %f \n",Myrank,time_taken);	
	if(Myrank!=0)
	{
		MPI_Send(&time_taken,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	if(Myrank==0)
	{
		time_arr[0]=time_taken;
		for(i=1;i<No_process;i++)
		{
			MPI_Recv(&time_arr[i],1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
		}
		double max=time_arr[0];
		for(i=1;i<No_process;i++)
		{
			if(time_arr[i]>max)
			max=time_arr[i];
		}
	printf("Time taken  is %f\n",max);
	printf("No of operation :%d\n",(2*Matrix_rows*Vector_size));
	printf("Peformance in mflops is : %f\n",(double )(2*Matrix_rows*Vector_size)/(max*1000000));
	}
		
	MPI_Finalize();
}
