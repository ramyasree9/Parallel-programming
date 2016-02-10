/*
***********************************************************************
		 C-DAC Tech Workshop PEMG-2010 
		     June 21 - 24, 2010

  Example 12	   : diag_comm.c

  Objective        : MPI program to create a communicator consisting of  
                     processes that lie on the diagonal in the  square 
                     grid of processes, arranged in the form of a matrix.

                     This example demonstrates the use of 

                        MPI_Init
                        MPI_Comm_rank
                        MPI_Comm_size
                        MPI_Comm_group
                        MPI_Group_incl
                        MPI_Comm_create
                        MPI_Finalize

  Input             : Communicator consisting of all  the processes

  OutPut            :  Processes of Communicator 

  Modified          : April 2010

  Created           : May 2008
                      National PARAM Supercomputing Facility


  Necessary Condition : Number of Processes should be perfect square 
                        and  less than 8. 

***********************************************************************
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

main(argc,argv)
int argc;
char **argv; 
{

        int	i,iproc, index;
	int	Numprocs, MyRank;
	int	New_numprocs, NewMyRank;
	int	*process_rank, Group_Diag;

	MPI_Group	GroupWorld,new_group;
	MPI_Comm	Diag_Group; 


  /* ....MPI Initialisation....*/

  	MPI_Init(&argc, &argv); 
  	MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
  	MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);


	Group_Diag=sqrt(Numprocs);

        if( sqrt(Numprocs)-Group_Diag != 0.0) {
           if(MyRank==0)
               printf("This program requires square number of processors\n");
               MPI_Finalize();
               exit(-1);
        }

	process_rank = (int *)malloc((Group_Diag) * sizeof(int));

	for(index=0; index < Group_Diag ; index++)
	    process_rank[index] = index*Group_Diag+index;
	
	if(MyRank==0)
	{	
	    printf("\nProcessors forming the diagonal group are \n"); 	
	    for(i=0;i<Group_Diag;i++)
   		printf("Processor %d\n",process_rank[i]); 
	}

	
	MPI_Comm_group(MPI_COMM_WORLD, &GroupWorld);
	MPI_Group_incl(GroupWorld, Group_Diag,process_rank,&new_group);
	MPI_Comm_create(MPI_COMM_WORLD,new_group,&Diag_Group); 
        if(MyRank%(Group_Diag+1)==0)
	{
	    MPI_Comm_rank(Diag_Group,&NewMyRank);
  	    MPI_Comm_size(Diag_Group,&New_numprocs);

	    printf("newnumprocs=%d\n",New_numprocs);
	    printf("NewRank in the diagonal group formed = %d\n", NewMyRank);
          }

/*  if(MyRank<8) MPI_Comm_free(&Diag_Group);*/

	MPI_Finalize(); 

}



