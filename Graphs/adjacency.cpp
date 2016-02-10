#include<iostream>
#include<cstring>
#include<cstdlib>
#include<list>
#include<fstream>
#include<algorithm>
#define size 315
using namespace std;
int main()
{
	ifstream fin ;
	list <int> L[size];
	int vertex[3] , i = 0 , j = 0;
	char * token;
	string line;
	char *temp;
	fin.open( "rocket_528" );
	while( fin )
	{
		getline( fin , line );
		temp = new char[50];
		strcpy(temp,line.c_str());
		token = new char[50];
		token	=	strtok(temp , " " ) ;
		i = 0;
		while(token != NULL)
		{
			vertex [ i ]	=	atoi(token);
			token	=	strtok( NULL , " " );
			i++ ;
		}
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
	ofstream fout ;
	fout.open("output.txt");
	for( i = 1 ; i < size ; i++ )
	{
		fout<<i<<" ";
		for( list<int> ::iterator it = L[i].begin(); it != L[i].end() ; it++ )
		fout<<(* it )<<" ";
		fout<<endl;
	}
	fin.close() ;
}
