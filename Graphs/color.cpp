/***********************************************************************
                           June 16, 2015

 Example               : color.cpp

 Objective             : To color all the vertices of a graph such that no two adjacent vertices will have same color.
	
 Algorithm     	       : Basic Greedy Coloring Algorithm:

			 1. Color first vertex with first color.
			 2. Do following for remaining V-1 vertices.
         			 a) Consider the currently picked vertex and color it with the 
         			    lowest numbered color that has not been used on any previously
           			    colored vertices adjacent to it. If all previously used colors 
           			    appear on vertices adjacent to v, assign a new color to it.

 Input                 : Each record (line) in the input file consists of ids of all the three vertices of a triangle.
                         
 Output                : Each record in the output file consists of a vertex id and its color.                        

 Created               : June-2015

 E-mail                : hpcfte@cdac.in

****************************************************************************/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#define size 1872

using namespace std;

/* driver program */
int main()
{
	ifstream fin ;
	list <int> L[size];
	int vertex_color[size];
	int vertex[3] , i = 0 , j = 0;
	char * token;
	string line;
	char *temp;
	fin.open( "datasets/sup/sup_1871.txt" );
	while( fin )
	{
		getline( fin , line );			
		temp	=	new char[50];
		strcpy(temp,line.c_str());
		token	=	new char[50];
		token	=	strtok(temp , " " ) ;
		i	=	0;

		/* Each line read from the input file is splitted using "strtok" and the id s of 
          	   the three vertices are stored in an array */ 										      while(token != NULL)
		{
			vertex [ i ]	=	atoi(token);
			token		=	strtok( NULL , " " );
			i++ ;
		}

		/* For each element of the array since the remaining two elements are adjacent to it,
		   they are added to it's adjacency list */
		for( i = 0 ; i < 3 ; i++ )
		{
			for( j = 0 ; j <3 ; j++ )
			{	
				 list <int>::iterator it;
				if( i != j )
				{
					 it = find( L[ vertex[i] ].begin() , L[ vertex[i] ].end(), vertex [j] );	
					if( it == L[ vertex [i] ].end() )
					{
						L[ vertex [ i ] ].push_back( vertex[ j ] );
					}
				}
			}
		}
	}

	// remove comments to print the adjacency lists of all vertcies 
       /* for( i = 1 ; i < size ; i++ )
	{
		cout<<i<<" ";
		for( list<int> ::iterator it = L[i].begin(); it != L[i].end() ; it++ )
		cout<<(* it )<<" ";
		cout<<endl;
	}*/
 
	fin.close() ;
	bool *marked;
	int index = -1,flag=0;
	
	/* colors of all the vertices are initialized to -1 */
	for( i = 1 ; i < size ; i++ )
	{
		vertex_color[i] = -1;	
	}
	
	/*  implementation of basic greedy coloring algorithm */
	for( i = 1 ; i < size ; i++)
	{
		if(index == -1)
		{
			index++;
			vertex_color[ i ]	=	index;
		}
		else
		{
				int d	=	0;
				marked	=	new bool[index+1];
				for( d = 0 ; d <= index ; d++ )
				{
					marked[d]	=	false;
				}
				for(list<int >:: iterator it = L[ i ].begin () ; it != L[i].end() ; it++)
				{
					if(vertex_color[*it] != -1)
					marked[vertex_color[*it ]]	=	true;
			
				}
			flag	=	0;
			for( d = 0 ; d <= index ; d++)
			{
				if(marked[d] == false)
				{
					vertex_color[i]	=	d;
					flag	=	1;
					break;
				}
			}
			if(flag == 0)
			{
				index++;
				vertex_color[i]	=	index;
			}
		}
	}	
	ofstream fout;
	fout.open("colors.txt");
	
	/* vertex id and its corresponding color are written into a file */
	for( i = 1 ; i < size ; i++ )
	fout<<i <<"\t:"<<vertex_color[i]<<endl; 

	cout<<"total colors used :"<<index+1<<endl;
}
