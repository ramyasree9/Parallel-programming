#include<stdio.h>
#include "input-matrix.h"
#include<stdlib.h>
double ** input_matrix(double **Matrix,int Matrix_rows,int Matrix_cols)
{
  	int     i;
  	        Matrix     =(double **)malloc(Matrix_rows*(sizeof(double*)) );
        
        for(i=0;i<Matrix_rows;i++)
	{ 
		Matrix[i]  =(double *)malloc(Matrix_cols*(sizeof(double )));
	}
  	return Matrix;
}
