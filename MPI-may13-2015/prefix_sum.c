
/******************************************************************************
		 C-DAC Tech Workshop PEMG-2010 
		     June 21 - 24, 2010

	Example1.8  : prefix_sum.c 

	Objective   : Calculate Prefix Sum on a Hyper-Cube using global 
		      reduction.

	Description : The MPI TAGS have been used in this assignment to get 
		      the desired output. Also, a NODE structure is defined and
		      its members are Hypercube Id, Value of the result, 
		      process Id. 

        Input       :  none

        OutPut      : Prefix sum

   Modified         : April 2010

   Created          : May 2008
                      National PARAM Supercomputing Facility

******************************************************************************/

#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define HC_DIMENSION 3
#define TOTAL_PROCESSES 8 

main (int argc, char *argv[]){

  /*    Definition of all elements of struct node  */
  typedef struct {
    int HC_Id;
    int Value;
    int Id_code;
  } node;

  /* Declare all variables */    

  node Process;
  int MyRank, MyPartner, Size, Message;
  int i, j, length;
  int Input, RecvData;

  int Destination, Destination_tag;
  int Source, Source_tag, root;

  /* The output is written in pfsum_result.[*] */
  node pfsum_result[TOTAL_PROCESSES];
  MPI_Status Status;

  /* MPI Initialisation */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &Size);
  MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

  /* Input : MyRank of the node */
  Input = MyRank;
  
  /* Assign values to the elemenss of the struct Process */
  Process.HC_Id = MyRank;
  Process.Value = Input;

  Message = Process.Value;

  /* Loop over the Hypercube dimension (d = 4) */
  for (i = 0; i < HC_DIMENSION; i++){

    /* Partner Identification through bitwise data manipulation (machine dependent) */
    MyPartner = Process.HC_Id ^ (int) pow(2,i);


    /* Send to partner and reeive from partner (Use tag for send and receive) */

    Destination = MyPartner ;
    Destination_tag = Process.HC_Id; 
    MPI_Send(&Message, 1, MPI_INT, Destination, Destination_tag, MPI_COMM_WORLD); 

    Source = MyPartner ;
    Source_tag = MyPartner; 
    MPI_Recv(&RecvData, 1, MPI_INT, Source, Source_tag, MPI_COMM_WORLD, &Status); 

   /* Update the Message and Value */
    Message+= RecvData;
    if (MyPartner < Process.HC_Id) 
      Process.Value += RecvData;
  }

  /* Get processor Id_code  */ 
  Process.Id_code = getpid();

  /* To collect the output of the programme on processor 0 */
  root = 0; 
  MPI_Gather(&Process, sizeof(node), MPI_CHAR, &pfsum_result, sizeof(node), MPI_CHAR, root, MPI_COMM_WORLD);
  /* Print the output of the programme on processor 0 */ 


  if(MyRank == 0) {
    printf("    HC_Id          Value       Id_code\n");

    for (i = 0; i < TOTAL_PROCESSES; i++)
     printf(" %9d    %9d  %12x     \n",pfsum_result[i].HC_Id, pfsum_result[i].Value,
                                        pfsum_result[i].Id_code);
  }

  MPI_Finalize();
  
}

