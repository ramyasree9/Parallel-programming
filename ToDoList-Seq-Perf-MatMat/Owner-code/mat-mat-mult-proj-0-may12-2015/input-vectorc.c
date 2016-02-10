#include<stdio.h>
#include "input-vector.h"
#include<stdlib.h>
double ** input_vector(double **Vector,int Vector_rows)
{	
  	int       i;
	Vector =  (double **)malloc(Vector_rows * sizeof(double *));
        for(i=0;i<Vector_rows;i++)
       	{
   		Vector[i]  =  (double *)malloc(sizeof(double));
	}
 	return Vector;
}
