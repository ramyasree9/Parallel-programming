#include<stdio.h>
#include "input.h"
void input(int *Matrix_rows,int *Matrix_cols,int *Vector_rows)
{
	int                 matrix_row_var,matrix_col_var,vector_row_var;
  	printf("enter no of rows and columns of matrix and no of rows of vector");
	scanf("%d%d%d",&matrix_row_var,&matrix_col_var,&vector_row_var);
	*Matrix_rows   =  matrix_row_var;
	*Matrix_cols   =  matrix_col_var;
	*Vector_rows   =  vector_row_var;
   
}
