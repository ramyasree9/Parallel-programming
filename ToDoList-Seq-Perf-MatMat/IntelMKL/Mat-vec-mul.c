#include<stdio.h>
#include "assert.h"
#include <time.h>
#include<stdlib.h>
#include<mkl.h>
#define ns 1000000
int main()
{
	struct timeval start,end;
	double *Matrix,*Vector,*Result_matrix,Time_taken;
	int i,j,k,Matrix_rows,Matrix_cols,Vector_size;
	srand48(time(NULL));
	printf("enter no of rows of matrix");
	scanf("%d",&Matrix_rows);
	printf("enter no of columns of matrix");
	scanf("%d",&Matrix_cols);
	printf("enter no of rows of vector");
	scanf("%d",&Vector_size);
	
	assert((Matrix_rows>1)&&(Matrix_cols>1)&&(Vector_size>1)&&(Matrix_cols==Vector_size));
	
	Matrix=(double *)malloc(Matrix_rows*Matrix_cols*(sizeof(double )));
	if(Matrix==NULL)
	{
		printf("memory not available");
		exit(-1);
	}
        Vector=(double *)malloc(Vector_size*(sizeof(double )));
	if(Vector==NULL)
	{
		printf("memory not available");
		exit(-1);
	}
	Result_matrix =(double *)malloc(Matrix_rows*(sizeof(double )));
	if(Result_matrix==NULL)
	{
		printf("memory not available");
		exit(-1);
	}

	for(i=0;i<Matrix_rows*Matrix_cols;i++)
	{
			Matrix[i]=drand48();
	}
	for(i=0;i<Vector_size;i++)
	{
		Vector[i]=drand48();
	}
	gettimeofday(&start,NULL);
	cblas_dgemv(CblasRowMajor,CblasNoTrans,Matrix_rows,Matrix_cols,1,Matrix,Matrix_rows,Vector,1,0,Result_matrix,1);
	gettimeofday(&end,NULL);
	if(end.tv_usec<start.tv_usec)
	{
		end.tv_usec=end.tv_sec+ns;
		end.tv_sec=end.tv_sec-1;
	}
	end.tv_usec=end.tv_usec-start.tv_usec;
	end.tv_sec=end.tv_sec-start.tv_sec;
	Time_taken=(double)end.tv_usec/ns;
	Time_taken=Time_taken+(double )end.tv_sec;
	printf("no of operations        : %d\n",2*Matrix_rows*Vector_size);
	printf("Time taken               : %f\n",Time_taken);
	printf("performance in Mflops is : %f\n",(2*Matrix_rows*Vector_size)/(Time_taken*ns));
	
/*	printf("resultant matrix is \n");
	for(i=0;i<Matrix_rows;i++)
	{
		printf("%f",Result_matrix[i]);
	}*/
	free(Matrix);
	free(Vector);
	free(Result_matrix);
}
