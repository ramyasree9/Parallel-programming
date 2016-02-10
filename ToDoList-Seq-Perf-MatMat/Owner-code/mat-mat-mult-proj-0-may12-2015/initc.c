#include<stdio.h>
#include<stdlib.h>
#include "init.h"

void init(double **Matrix,double **Vector,int Matrix_rows,int Matrix_cols,int Vector_rows)
{
        int     i,j;
	for(i=0;i<Matrix_rows;i++)
	{
		for(j=0;j<Matrix_cols;j++)
		{
    			
		//	Matrix[i][j]=(double)(i+1)*(j+1);
			Matrix[i][j]=rand()/99.0;
		}	
	
	}
        for(j=0;j<Vector_rows;j++)
	{
	//	Vector[j][0]=(double)j+1;
		Vector[j][0]=rand()/98.0;
	}
}
