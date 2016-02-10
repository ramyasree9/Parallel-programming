/*
*******************************************************************
		 C-DAC Tech Workshop PEMG-2010 
		     June 21 - 24, 2010

    Example 2.4		: allgather.c

    Objective           : To gather data from all the processs  

                          This example demonstrates the use of 
                          MPI_Init
                          MPI_Comm_rank
                          MPI_Comm_size
                          MPI_Allgather 
                          MPI_Barrier 
                          MPI_Finalize

    Input               : Data from files (gdata0,gdata1,gdata2,gdata3,gdata4,
                          gdata5,gdata6,gdata7) is available on each process.

    Output              : Gathered data is printed on each process.

    Modified            : April 2010

    Created             : May 2008
                          National PARAM Supercomputing Facility

    Necessary Condition : Number of Processes should be 
                          less than or equal to 8

*******************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mpi.h"

main(int argc, char** argv) {

  /* .......Variables Initialisation ......*/
  MPI_Status status;     
  int n_size, Numprocs, MyRank, root;
  int i, scatter_size;
  int *Input_A, *Output;
  char	str[4], filename[50] = "./data/gdata";
  FILE *fp;

  /* ........MPI Initialisation .......*/
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);

  /*  ....You can not have more than 8 processors....*/

    if(Numprocs>8)
    {
       printf("\nNumber of processor should be less than 9");
       MPI_Finalize();
       exit(-1);
    }

    /* .......Read the Input file ......*/

    sprintf(str, "%d", MyRank);
    strcat(filename, str);
    if ((fp = fopen (filename, "r")) == NULL)
    {
       printf("\nCan't open input file");
       MPI_Finalize(); 
       exit(-1);
    }
    fscanf(fp, "%d", &n_size);     

    /* ...Allocate memory and read data .....*/

    Input_A = (int *)malloc(n_size*sizeof(int));

    for(i=0; i< n_size; i++) 
        fscanf(fp, "%d", &Input_A[i]);     
    

    MPI_Barrier(MPI_COMM_WORLD);

    Output = (int *)malloc(n_size*Numprocs*sizeof(int));

    MPI_Allgather (Input_A, n_size, MPI_INT, Output, n_size, MPI_INT, 
	       	  MPI_COMM_WORLD); 

    MPI_Barrier(MPI_COMM_WORLD);

    printf("\nResults of Gathering data on processor %d: %d", 
						MyRank, n_size*Numprocs);
    printf("\n-----------------------------------------------\n");

    for(i = 0; i < n_size*Numprocs; ++i)
    {
       if((i%10)==0) printf("\n"); 
       printf(" %d ", Output[i]);
    }
    fclose(fp);

    MPI_Finalize(); 

}
