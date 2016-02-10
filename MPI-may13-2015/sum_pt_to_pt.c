/*
*********************************************************************
		 C-DAC Tech Workshop PEMG-2010 
		     June 21 - 24, 2010

  Example 1.3         : sum_pt_to_pt.c

  Objective           : To find sum of 'n' integers on 'p' processors using
                        point-to-point communication libraries calls

                        This example demonstrates the use of 
                        MPI_Init
                        MPI_Comm_rank
                        MPI_Comm_size
                        MPI_Recv
                        MPI_Send
                        MPI_Finalize

  Input               : Automatic input generation
                        The rank of each process is input on each process.

  Output              : Process with Rank 0 should print the sum of 'n' values

  Modified            : April 2010
  Created             : May 2008
                         National PARAM Supercomputing Facility

  
  Necessary           : Number of Processes should be less than
  Condition             or equal to 8


***********************************************************************
*/



#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[])
{
    int iproc;
    int MyRank, Numprocs, Root = 0;
    int value, sum = 0;
    int	Source, Source_tag;
    int Destination, Destination_tag;
    MPI_Status status;


    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);

    if(MyRank == Root){

       for(iproc = 1 ; iproc < Numprocs ; iproc++){
           Source     = iproc;
	   Source_tag = 0;

	   MPI_Recv(&value, 1, MPI_INT, Source, Source_tag, 
		     MPI_COMM_WORLD, &status);
	   sum = sum + value;
       }
       printf("MyRank = %d, SUM = %d\n", MyRank, sum);
    }
    else{
	Destination     = 0;
	Destination_tag = 0;

	MPI_Send(&MyRank, 1, MPI_INT, Destination, Destination_tag, 
		  MPI_COMM_WORLD);
    }

    MPI_Finalize();

}



