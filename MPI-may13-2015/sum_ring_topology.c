/*
**********************************************************************
		 C-DAC Tech Workshop PEMG-2010 
		     June 21 - 24, 2010

  Example 1.5	      : sum_ring_topology.c

  Objective           : To find sum of 'n' integers on 'p' processors using 
                        Point-to-Point communication library calls and ring 
                        topology. 

                        This example demonstrates the use of 
                        MPI_Init
                        MPI_Comm_rank
                        MPI_Comm_size
                        MPI_Send
                        MPI_Recv
                        MPI_Finalize

  Input               : Automatic input generation
                        The rank of each process is input on each process.

  Output              : Process with Rank 0 should print the sum of 'n' values 

  Modified            : April 2010
  Created             : May 2008
                        National PARAM Supercomputing Facility

  Necessary           : Number of Processes should be less than 
  Condtion              or equal to 8.

***********************************************************************
*/

 

#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[])
{
    int         MyRank, Numprocs, Root = 0;
    int         value, sum = 0;
    int	        Source, Source_tag;
    int         Destination, Destination_tag;
    MPI_Status  status;

	 /* Initialize MPI */
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
   
    if (MyRank == Root){
	Destination     = MyRank + 1;
	Destination_tag = 0;
	MPI_Send(&MyRank, 1, MPI_INT, Destination, Destination_tag, 
		  MPI_COMM_WORLD);
    }

    else{
       if(MyRank<Numprocs-1){
	  Source     = MyRank - 1;
	  Source_tag = 0;

	  MPI_Recv(&value, 1, MPI_INT, Source, Source_tag, 
		    MPI_COMM_WORLD, &status);
	  sum  = MyRank + value;
	  Destination = MyRank + 1;
	  Destination_tag = 0;
	  MPI_Send(&sum, 1, MPI_INT, Destination, Destination_tag, 
		    MPI_COMM_WORLD);
	}
	else{
	   Source     = MyRank - 1;
	   Source_tag = 0;
	   MPI_Recv(&value, 1, MPI_INT, Source, Source_tag, 
		     MPI_COMM_WORLD, &status);
	   sum = MyRank + value;
	}
    } 
    
    if (MyRank == Root)
    {
	Source     = Numprocs - 1;
	Source_tag = 0;
	MPI_Recv(&sum, 1, MPI_INT, Source, Source_tag, 
		  MPI_COMM_WORLD, &status);

	printf("MyRank %d Final SUM %d\n", MyRank, sum);

    }

    if(MyRank == (Numprocs - 1)){
       Destination     = 0;
       Destination_tag = 0;
       MPI_Send(&sum, 1, MPI_INT, Destination, Destination_tag, 
		 MPI_COMM_WORLD);
    }

    MPI_Finalize();

}




